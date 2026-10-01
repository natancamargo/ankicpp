#pragma once

#include <cstdint>
#include <string>
#include <vector>
namespace ankicpp {
class NoteTypeDTO {
public:
  uint32_t id;
  std::string name;
  uint32_t mtime_secs;
  uint32_t usn;
  std::vector<unsigned char> config;
};
} // namespace ankicpp
