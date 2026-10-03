#include "util/identifyable.h"
#include <cstdint>

namespace ankicpp {
Identifyable::Identifyable() : _id(0) {}

std::uint32_t Identifyable::getId() { return _id; }
void Identifyable::setId(std::uint32_t id) { _id = id; }

bool Identifyable::operator==(Identifyable &rhs) {
  return getId() == rhs.getId();
}
bool Identifyable::operator!=(Identifyable &rhs) {
  return !(getId() == rhs.getId());
}
bool Identifyable::operator<(Identifyable &rhs) {
  return getId() < rhs.getId();
}
} // namespace ankicpp
