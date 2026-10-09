#include "ankicpp/export.h"
#include "compression/compression.h"
#include "database/database.h"
#include "deck/deck.h"
#include <cstdio>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <string_view>

namespace ankicpp {
Error error = Error::EXPORT_NO_ERROR;

bool exportDeck(const std::shared_ptr<Deck> &deck, std::string_view filename) {
  std::cout << std::format("export: Starting...\n");

  error = Error::EXPORT_NO_ERROR;

  const std::filesystem::path outPath = std::filesystem::path(filename.data());
  const std::filesystem::path parentPath = outPath.parent_path();
  const std::filesystem::path mediaPath =
      parentPath / std::filesystem::path("media");
  const std::filesystem::path metaPath =
      parentPath / std::filesystem::path("meta");
  const std::filesystem::path databasePath =
      parentPath / std::filesystem::path("collection.anki21b.db");
  const std::filesystem::path zstdDatabasePath =
      parentPath / std::filesystem::path("collection.anki21b");

  if (!createFiles(outPath, metaPath, mediaPath, databasePath)) {    
    return false;
  }

  if (!populateDatabase(deck, databasePath.string())) {
    return false;
  }

  const std::vector<std::string> zstdInputs = {databasePath.string()};
  const std::vector<std::string> zstdOutputs = {zstdDatabasePath.string()};
  const std::vector<std::string> zipInputs = {
      metaPath.string(), mediaPath.string(), zstdDatabasePath.string()};
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
        0x28, 0xb5, 0x2f, 0xfd, 0x20, 0x00, 0x01, 0x00, 0x00};
    metaOutstream.write(reinterpret_cast<const char *>(&metaContent),
                        sizeof(metaContent));
    mediaOutstream.write(reinterpret_cast<const char *>(&mediaContent),
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
    std::cout << std::format("export: Failed.\n");
    return false;
  }

  if (!database::connect(filename)) {
    std::cout << std::format("export: Failed.\n");
    return false;
  }
  if (!database::createDatabase()) {
    database::disconnect();
    std::cout << std::format("export: Failed.\n");
    return false;
  }
  if (!database::populateDatabase(deck)) {
    database::disconnect();
    std::cout << std::format("export: Failed.\n");
    return false;
  }
  if (!database::disconnect()) {
    return false;
  }

  return true;
}
} // namespace ankicpp
