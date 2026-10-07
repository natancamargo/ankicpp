#pragma once

#include <cstdint>
#include <soci/soci.h>
#include <string>
#include <vector>
namespace ankicpp {
class TemplateDTO {
public:
 std::int64_t ntid;
 std::int64_t ord;
  std::string name;
 std::int64_t mtime_secs;
 std::int64_t usn;
  std::vector<unsigned char> config;
};
} // namespace ankicpp
