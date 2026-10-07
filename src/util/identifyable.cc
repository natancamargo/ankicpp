#include "util/identifyable.h"
#include <cstdint>
#include <cstdlib>
#include <random>

namespace ankicpp {
Identifyable::Identifyable() { _id = generateRandomId(); }

std::int64_t Identifyable::getId() { return _id; }
void Identifyable::setId(std::int64_t id) { _id = id; }

std::int64_t Identifyable::generateRandomId() {
  std::random_device rd;
  std::mt19937_64 gen(rd());

  std::uniform_int_distribution<std::int64_t> dist(
      0, std::numeric_limits<std::int64_t>::max());

  return dist(gen);
}

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
