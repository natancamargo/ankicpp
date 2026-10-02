#pragma once

#include <string_view>
#include <vector>

namespace ankicpp {
enum class CompressError {
  NONE,
  UNKNOWN_ERROR,
  FILE_NOT_FOUND_ERROR,
  FILE_READING_ERROR,
  MINIZIP_ERROR
};
extern CompressError compressError;
bool compress(std::vector<std::string_view> inputs, std::string_view output);
} // namespace ankicpp
