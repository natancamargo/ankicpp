#pragma once

#include <cstdint>
#include <string>
#include <vector>
namespace ankicpp {
class FieldDTO {
public:
 std::int64_t ntid;
 std::int64_t ord;
  std::string name;
  std::vector<unsigned char> config;
};
} // namespace ankicpp
