#include "compression/compression.h"

#include "compression/zip-utils.h"
#include "compression/zstd-utils.h"
#include <string>

namespace ankicpp {
bool compress(const std::vector<std::string> &zstdInputs,
              const std::vector<std::string> &zstdOutputs,
              const std::vector<std::string> &zipInputs,
              const std::string &zipOutput) {
  for (size_t i = 0; i < zstdInputs.size(); i++) {
    const std::string inputZstd = zstdInputs[i];
    const std::string outputZstd = zstdOutputs[i];
    if (!zstd::compress(inputZstd, outputZstd)) {
      return false;
    }
  }
  if (!zip::compress(zipInputs, zipOutput)) {
    return false;
  }
  return true;
}
} // namespace ankicpp
