#pragma once

#include <cstdint>
namespace ankicpp {
class Identifyable {
public:
  Identifyable();

  std::uint32_t getId();
  void setId(std::uint32_t id);

  bool operator==(Identifyable &rhs);
  bool operator!=(Identifyable &rhs);
  bool operator<(Identifyable &rhs);

protected:
  std::uint32_t _id;
};
} // namespace ankicpp
