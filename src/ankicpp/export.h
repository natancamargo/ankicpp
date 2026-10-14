#pragma once

#include "deck/deck.h"
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

bool exportDeck(const std::shared_ptr<Deck> &deck, std::string_view filename);
bool createFiles(std::filesystem::path outPath, std::filesystem::path metaPath,
                 std::filesystem::path mediaPath,
                 std::filesystem::path databasePath);
bool populateDatabase(const std::shared_ptr<Deck> &deck, std::string filename);
const std::tuple<bool, std::vector<std::filesystem::path>>
populateMedia(const std::shared_ptr<Deck> &deck,
              const std::filesystem::path &mediaPath,
              const std::filesystem::path &directoryOutPath,
              std::set<std::string> &medias,
              std::vector<std::filesystem::path> &mediaOutputPaths);
bool writeToMediaRootFile(const std::filesystem::path &mediaPath,
                          const std::string &media);
} // namespace ankicpp
