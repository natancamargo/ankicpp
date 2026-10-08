#pragma once

#include "deck/deck.h"
#include <filesystem>
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

  EXPORT_DATABASE_ERROR,

  DATA_DECK_EMPTY_ERROR,
  DATA_NOTE_WITHOUT_TYPE_ERROR,
};
extern Error error;

bool exportDeck(Deck deck, std::string_view filename);
bool createFiles(std::filesystem::path outPath, std::filesystem::path metaPath,
                 std::filesystem::path mediaPath,
                 std::filesystem::path databasePath);
bool populateDatabase(Deck deck, std::string filename);
} // namespace ankicpp
