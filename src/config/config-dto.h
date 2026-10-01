#pragma once

#include <cstdint>
#include <string>
#include <vector>
namespace ankicpp {
class ConfigDTO {
public:
  std::string KEY;
  std::uint32_t usn;
  std::uint32_t mtime_secs;
  std::vector<unsigned char> val;
};
} // namespace ankicpp
