#pragma once

#include <cstdint>
#include <string>
#include <vector>
namespace ankicpp {
class FieldDTO {
public:
  uint32_t ntid;
  uint32_t ord;
  std::string name;
  std::vector<unsigned char> config;
};
} // namespace ankicpp
