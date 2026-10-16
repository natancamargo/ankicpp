#pragma once

#include "deck/deck.h"
#include "resources/proto/media.pb.h"
#include <filesystem>
#include <memory>
#include <string_view>
namespace ankicpp {
enum class Error {
  EXPORT_NO_ERROR,
  EXPORT_UNKNOWN_ERROR,
  EXPORT_FILE_READING_ERROR,
  EXPORT_FILE_WRITING_ERROR,

  EXPORT_COMPRESS_FILE_NOT_FOUND_ERROR,
  EXPORT_COMPRESS_FILE_READING_ERROR,
  EXPORT_COMPRESS_MINIZIP_ERROR,
  EXPORT_COMPRESS_ZSTD_ERROR,

  EXPORT_MEDIA_ERROR,

  EXPORT_DATABASE_ERROR,

  DATA_DECK_EMPTY_ERROR,
  DATA_NOTE_WITHOUT_TYPE_ERROR,
};
extern Error error;

struct ExportContext {
  std::shared_ptr<Deck> deck;
  const std::filesystem::path &out;
  const std::filesystem::path &meta;
  const std::filesystem::path &media;
  const std::filesystem::path &zstdMedia;
  const std::filesystem::path &database;
  const std::filesystem::path &zstdDatabase;
  std::set<std::filesystem::path> &medias;
  std::vector<std::string> &zip;  
  anki::MediaEntries &ankiMedias;
};

bool exportDeck(const std::shared_ptr<Deck> &deck, std::string_view filename);
bool createFiles(ExportContext &context);
bool populateDatabase(ExportContext &context);
bool populateMedia(ExportContext &context);
bool readMedia(ExportContext &context, const std::filesystem::path &singleMediaPath);
bool writeToMediaRootFile(ExportContext &context);
} // namespace ankicpp
