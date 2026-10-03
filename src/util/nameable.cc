#include "util/nameable.h"

namespace ankicpp {
Nameable::Nameable() {}
Nameable::Nameable(std::string name) : _name(name) {}

std::string Nameable::getName() { return _name; }
void Nameable::setName(std::string name) { _name = name; }
} // namespace ankicpp
