#pragma once

#include <string>
#include <vector>

namespace ankicpp {
bool compress(const std::vector<std::string> &zstdInputs,
              const std::vector<std::string> &zstdOutputs,
              const std::vector<std::string> &zipInputs,
              const std::string &zipOutput);
} // namespace ankicpp
