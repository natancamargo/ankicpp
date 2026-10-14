#include "ankicpp/export.h"
#include "compression/compression.h"
#include "database/database.h"
#include "deck/deck.h"
#include <cstddef>
#include <cstdio>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <memory>
#include <string_view>
#include <tuple>
#include <unistd.h>

namespace ankicpp {
Error error = Error::EXPORT_NO_ERROR;

bool exportDeck(const std::shared_ptr<Deck> &deck, std::string_view filename) {
  std::cout << std::format("\nexport: Starting...\n");

  error = Error::EXPORT_NO_ERROR;

  const std::filesystem::path outPath = std::filesystem::path(filename.data());
  const std::filesystem::path directoryOutPath = outPath.parent_path();
  const std::filesystem::path mediaPath =
      directoryOutPath / std::filesystem::path("media");
  const std::filesystem::path metaPath =
      directoryOutPath / std::filesystem::path("meta");
  const std::filesystem::path databasePath =
      directoryOutPath / std::filesystem::path("collection.anki21b.db");
  const std::filesystem::path zstdDatabasePath =
      directoryOutPath / std::filesystem::path("collection.anki21b");

  if (!createFiles(outPath, metaPath, mediaPath, databasePath)) {
    std::cout << std::format("export: Failed.\n");
    return false;
  }

  std::set<std::string> medias;
  std::vector<std::filesystem::path> mediaOutputPaths;
  const std::tuple<bool, std::vector<std::filesystem::path>> mediaResult =
      populateMedia(deck, mediaPath, directoryOutPath, medias,
                    mediaOutputPaths);
  if (!std::get<0>(mediaResult)) {
    std::cout << std::format("export: Failed.\n");
    return true;
  }

  if (!populateDatabase(deck, databasePath.string())) {
    std::cout << std::format("export: Failed.\n");
    return false;
  }

   // meta, media and collection.anki21b.db  
  const std::vector<std::string> zstdInputs = {databasePath.string()};
  const std::vector<std::string> zstdOutputs = {zstdDatabasePath.string()};
  std::vector<std::string> zipInputs = {
      metaPath.string(), mediaPath.string(), zstdDatabasePath.string()};

  // media output files (0, 1, 2)
  for (std::vector<std::filesystem::path>::iterator it =
           mediaOutputPaths.begin();
       it != mediaOutputPaths.end(); it++) {
    zipInputs.push_back(it->string());
  }

  // compress all files  
  if (!compress(zstdInputs, zstdOutputs, zipInputs, outPath.string())) {
    std::cout << std::format("export: Failed.\n");
    return false;
  }

  std::cout << std::format("export: Done.\n");
  return true;
}
bool createFiles(std::filesystem::path outPath, std::filesystem::path metaPath,
                 std::filesystem::path mediaPath,
                 std::filesystem::path databasePath) {
  std::cout << std::format("export: Exporting to folder: {}\n",
                           outPath.parent_path().c_str());

  std::ofstream metaOutstream = std::ofstream(metaPath, std::ios::binary);
  std::ofstream mediaOutstream = std::ofstream(mediaPath, std::ios::binary);
  std::ofstream databaseOutstream = std::ofstream(databasePath);

  if (!metaOutstream.is_open() || !mediaOutstream.is_open() ||
      !databaseOutstream.is_open()) {
    perror(std::format(
               "export: Error while opening the files. Directory {} exists?.\n",
               metaPath.parent_path().string())
               .c_str());
    error = Error::EXPORT_FILE_READING_ERROR;
    return false;
  }

  try {
    metaOutstream.exceptions(metaOutstream.failbit | metaOutstream.badbit);
    mediaOutstream.exceptions(mediaOutstream.failbit | mediaOutstream.badbit);
    databaseOutstream.exceptions(databaseOutstream.failbit |
                                 databaseOutstream.badbit);

    constexpr const unsigned char metaContent[] = {0x08, 0x03};
    constexpr const unsigned char mediaContent[] = {
        0x28, 0xb5, 0x2f, 0xfd, 0x00, 0x58, 0x39, 0x01, 0x00, 0x0a, 0x25};
    metaOutstream.write(reinterpret_cast<const char *>(metaContent),
                        sizeof(metaContent));
    mediaOutstream.write(reinterpret_cast<const char *>(mediaContent),
                         sizeof(mediaContent));

  } catch (const std::ifstream::failure &e) {
    error = Error::EXPORT_FILE_WRITING_ERROR;
    std::cout << std::format("Error:\n{}\nError code: {}\n", e.what(),
                             e.code().value());
    std::cout << std::format("export: Failed.\n");
    return false;
  }

  metaOutstream.close();
  mediaOutstream.close();
  databaseOutstream.close();

  return true;
}
bool populateDatabase(const std::shared_ptr<Deck> &deck, std::string filename) {
  if (!deck->generateCards()) {
    return false;
  }

  if (!database::connect(filename)) {
    return false;
  }
  if (!database::createDatabase()) {
    database::disconnect();
    return false;
  }
  if (!database::populateDatabase(deck)) {
    database::disconnect();
    return false;
  }
  if (!database::disconnect()) {
    return false;
  }

  return true;
}
const std::tuple<bool, std::vector<std::filesystem::path>>
populateMedia(const std::shared_ptr<Deck> &deck,
              const std::filesystem::path &mediaPath,
              const std::filesystem::path &directoryOutPath,
              std::set<std::string> &medias,
              std::vector<std::filesystem::path> &mediaOutputPaths) {
  // 24 bytes of each image
  // size+index+sha1
  for (const std::shared_ptr<Note> &note : deck->getNotes()) {
    medias.insert(note->getMedias().begin(), note->getMedias().end());
  }
  for (const std::shared_ptr<Deck> &_deck : deck->getDecks()) {
    const std::tuple<bool, std::vector<std::filesystem::path>> childResult =
        populateMedia(_deck, mediaPath, directoryOutPath, medias,
                      mediaOutputPaths);
    if (!std::get<0>(childResult)) {
      error = Error::EXPORT_MEDIA_ERROR;
      return std::make_tuple(false, mediaOutputPaths);
    } else {
      const std::vector<std::filesystem::path> &childMediaOutPaths =
          std::get<1>(childResult);
      mediaOutputPaths.insert(mediaOutputPaths.end(),
                              childMediaOutPaths.begin(),
                              childMediaOutPaths.end());
    }
  }

  if (!deck->getParent().lock() && medias.size() != 0) {
    for (std::set<std::string>::iterator it = medias.begin();
         it != medias.end(); it++) {
      std::size_t index = std::distance(medias.begin(), it);
      const std::filesystem::path mediaInputPath = std::filesystem::path{*it};
      std::filesystem::path mediaOutPath =
          directoryOutPath / std::filesystem::path{std::to_string(index)};
      mediaOutputPaths.push_back(mediaOutPath);
      std::filesystem::copy(mediaInputPath, mediaOutPath,
                            std::filesystem::copy_options::overwrite_existing);
      writeToMediaRootFile(mediaPath, *it);
    }
  }

  return std::make_tuple(true, mediaOutputPaths);
}
bool writeToMediaRootFile(const std::filesystem::path &mediaPath,
                          const std::string &media) {
  std::ofstream mediaOutstream =
      std::ofstream(mediaPath, std::ios::app | std::ios::binary);

  if (!mediaOutstream.is_open()) {
    perror("export: Error while persisting media.");
    error = Error::EXPORT_MEDIA_ERROR;
    return false;
  }

  try {
    mediaOutstream.exceptions(mediaOutstream.failbit | mediaOutstream.badbit);

    constexpr const unsigned char initOfFile[] = {0x0a, 0x0a};
    constexpr const unsigned char endOfFile[] = {
        0x10, 0xfa, 0x69, 0x1a, 0x14, 0x4c, 0x7d, 0x63, 0xdc,
        0xb0, 0x87, 0xe1, 0xa5, 0xf4, 0x61, 0x67, 0x59, 0x84,
        0x61, 0xd9, 0xc7, 0x71, 0x7a, 0x09, 0xd6};
    mediaOutstream.write(reinterpret_cast<const char *>(initOfFile),
                         sizeof(initOfFile));
    const std::string mediaFileName =
        std::filesystem::path{media}.filename().string();
    mediaOutstream.write(mediaFileName.c_str(), mediaFileName.size());

    mediaOutstream.write(reinterpret_cast<const char *>(endOfFile),
                         sizeof(endOfFile));
  } catch (const std::ifstream::failure &e) {
    error = Error::EXPORT_MEDIA_ERROR;
    std::cout << std::format("export:\n{}\nError code: {}\n", e.what(),
                             e.code().value());
    return false;
  }

  mediaOutstream.close();
  return true;
}
} // namespace ankicpp
