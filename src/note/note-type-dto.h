#pragma once

#include <cstdint>
#include <string>
#include <vector>
namespace ankicpp {
class NoteTypeDTO {
public:
 std::int64_t id;
  std::string name;
 std::int64_t mtime_secs;
 std::int64_t usn;
  std::vector<unsigned char> config;
};
} // namespace ankicpp
