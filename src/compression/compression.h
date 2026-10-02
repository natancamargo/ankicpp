#pragma once

#include <string>
#include <vector>

namespace ankicpp {
enum class CompressError {
  NONE,
  UNKNOWN_ERROR,
  FILE_NOT_FOUND_ERROR,
  FILE_READING_ERROR,
  MINIZIP_ERROR,
  ZSTD_ERROR
};
extern CompressError compressError;
bool compress(const std::vector<std::string> &zstdInputs,
              const std::vector<std::string> &zstdOutputs,
              const std::vector<std::string> &zipInputs,
              const std::string &zipOutput);
} // namespace ankicpp
