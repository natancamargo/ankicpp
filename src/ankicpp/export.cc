#include "ankicpp/export.h"
#include "compression/zip-utils.h"
#include "compression/zstd-utils.h"
#include "database/database.h"
#include "deck/deck.h"
#include "resources/proto/media.pb.h"
#include "resources/proto/meta.pb.h"
#include "util/crypto.h"
#include <cstddef>
#include <cstdio>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <memory>
#include <string_view>
#include <unistd.h>

namespace ankicpp {
Error error = Error::EXPORT_NO_ERROR;

bool exportDeck(const std::shared_ptr<Deck> &deck, std::string_view filename) {
  std::cout << std::format("\nexport: Starting...\n");

  error = Error::EXPORT_NO_ERROR;

  const std::filesystem::path out = std::filesystem::path(filename.data());
  const std::filesystem::path dirOut = out.parent_path();
  const std::filesystem::path media =
      dirOut / std::filesystem::path("media.raw");
  const std::filesystem::path zstdMedia =
      dirOut / std::filesystem::path("media");
  const std::filesystem::path meta = dirOut / std::filesystem::path("meta");
  const std::filesystem::path database =
      dirOut / std::filesystem::path("collection.anki21b.db");
  const std::filesystem::path zstdDatabase =
      dirOut / std::filesystem::path("collection.anki21b");

  std::set<std::filesystem::path> medias;
  std::vector<std::filesystem::path> mediaOuts;

  anki::MediaEntries ankiMedias;

  std::vector<std::string> zip;

  ExportContext context = {deck,     out,          meta,   media, zstdMedia,
                           database, zstdDatabase, medias, zip,   ankiMedias};

  if (!createFiles(context) || !writeToMeta(context) ||
      !writeToMedia(context) || !writeToDatabase(context)) {
    std::cout << std::format("export: Failed.\n");
    return false;
  }

  // zstd compress files
  if (!zstd::compress(database.string(), zstdDatabase.string()) ||
      !zstd::compress(media.string(), zstdMedia.string())) {
    std::cout << std::format("export: Failed.\n");
    return false;
  }

  // zip compress
  // meta, media and collection.anki21b.db
  context.zip.insert(context.zip.end(), {meta.string(), zstdMedia.string(),
                                         zstdDatabase.string()});
  if (!zip::compress(context.zip, out.string())) {
    std::cout << std::format("export: Failed.\n");
    return false;
  }

  std::cout << std::format("export: Done.\n");
  return true;
} // namespace ankicpp
bool createFiles(ExportContext &context) {
  std::cout << std::format("export: Exporting to folder: {}\n",
                           context.out.parent_path().c_str());

  std::ofstream metaOutstream = std::ofstream(context.meta, std::ios::binary);
  std::ofstream mediaOutstream = std::ofstream(context.media, std::ios::binary);
  std::ofstream databaseOutstream = std::ofstream(context.database);

  if (!metaOutstream.is_open() || !mediaOutstream.is_open() ||
      !databaseOutstream.is_open()) {
    perror(std::format(
               "export: Error while opening the files. Directory {} exists?.\n",
               context.meta.parent_path().string())
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
    metaOutstream.write(reinterpret_cast<const char *>(metaContent),
                        sizeof(metaContent));
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
bool writeToDatabase(ExportContext &context) {
  if (!context.deck->generateCards()) {
    return false;
  }

  if (!database::connect(context.database.string())) {
    return false;
  }
  if (!database::createDatabase()) {
    database::disconnect();
    return false;
  }
  if (!database::writeToDatabase(context.deck)) {
    database::disconnect();
    return false;
  }
  if (!database::disconnect()) {
    return false;
  }

  return true;
}
bool writeToMedia(ExportContext &context) {
  std::shared_ptr<Deck> &oldDeck = context.deck;
  for (const std::shared_ptr<Note> &note : context.deck->getNotes()) {
    context.medias.insert(note->getMedias().begin(), note->getMedias().end());
  }
  for (const std::shared_ptr<Deck> &_deck : context.deck->getDecks()) {
    context.deck = _deck;
    if (!writeToMedia(context)) {
      error = Error::EXPORT_MEDIA_ERROR;
      return false;
    }
  }

  // Return the oldDeck has primary deck
  context.deck = oldDeck;

  // Executed only at root deck
  if (!context.deck->getParent().lock() && context.medias.size() != 0) {
    for (std::set<std::filesystem::path>::iterator it = context.medias.begin();
         it != context.medias.end(); it++) {
      std::size_t index = std::distance(context.medias.begin(), it);
      const std::filesystem::path mediaInputPath = *it;
      std::filesystem::path zstdMediaOutPath =
          context.out.parent_path() /
          std::filesystem::path{std::to_string(index)};

      zstd::compress(mediaInputPath, zstdMediaOutPath);
      context.zip.push_back(zstdMediaOutPath);

      readMedia(context, mediaInputPath);
    }

    writeToMediaRoot(context);
  }

  return true;
}
bool readMedia(ExportContext &context,
               const std::filesystem::path &oneMediaPath) {
  // File size
  size_t size = std::filesystem::file_size(oneMediaPath);

  // Read media content
  std::ifstream out = std::ifstream{oneMediaPath.string()};

  if (!out.is_open()) {
    perror("export: Error while persisting media.");
    error = Error::EXPORT_MEDIA_ERROR;
    return false;
  }
  char *contents = new char[size];
  out.read(contents, size);
  out.close();

  // write to protobuf file "media.raw"
  anki::MediaEntries_MediaEntry *ankiMedia = context.ankiMedias.add_entries();
  ankiMedia->set_name(oneMediaPath.filename());
  ankiMedia->set_size(size);
  ankiMedia->set_sha1(sha1(contents));

  return true;
}
bool writeToMediaRoot(ExportContext &context) {
  std::ofstream mediaOutstream =
      std::ofstream(context.media, std::ios::app | std::ios::binary);

  if (!mediaOutstream.is_open()) {
    perror("export: Error while persisting media.");
    error = Error::EXPORT_MEDIA_ERROR;
    return false;
  }

  try {
    mediaOutstream.exceptions(mediaOutstream.failbit | mediaOutstream.badbit);
    context.ankiMedias.SerializeToOstream(&mediaOutstream);
  } catch (const std::ifstream::failure &e) {
    error = Error::EXPORT_MEDIA_ERROR;
    std::cout << std::format("export:\n{}\nError code: {}\n", e.what(),
                             e.code().value());
    return false;
  }

  mediaOutstream.close();
  return true;
}
bool writeToMeta(ExportContext &context) {
  anki::PackageMetadata meta;
  meta.set_version(
      anki::PackageMetadata_Version::PackageMetadata_Version_VERSION_LATEST);

  std::ofstream metaOutstream =
      std::ofstream(context.meta, std::ios::app | std::ios::binary);

  if (!metaOutstream.is_open()) {
    perror("export: Error while persisting meta.");
    error = Error::EXPORT_MEDIA_ERROR;
    return false;
  }

  try {
    metaOutstream.exceptions(metaOutstream.failbit | metaOutstream.badbit);
    meta.SerializeToOstream(&metaOutstream);
  } catch (const std::ifstream::failure &e) {
    error = Error::EXPORT_MEDIA_ERROR;
    std::cout << std::format("export:\n{}\nError code: {}\n", e.what(),
                             e.code().value());
    return false;
  }

  metaOutstream.close();

  return true;
}
} // namespace ankicpp
