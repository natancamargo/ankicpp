#pragma once

#include <cstdint>
namespace ankicpp {
class Identifyable {
public:
  Identifyable();

  std::int64_t getId();
  void setId(std::int64_t id);

  static std::int64_t generateRandomId();
  
  bool operator==(Identifyable &rhs);
  bool operator!=(Identifyable &rhs);
  bool operator<(Identifyable &rhs);

protected:
  std::int64_t _id;
};
} // namespace ankicpp
