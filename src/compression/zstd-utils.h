#pragma once

#include <string>
#include <vector>
namespace ankicpp {
  namespace zstd {
    bool compress(std::string input, std::string output);
  }
} // namespace ankicpp
