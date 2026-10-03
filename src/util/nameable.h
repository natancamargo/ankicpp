#pragma once

#include <string>
namespace ankicpp {
class Nameable {
public:
  Nameable();
  Nameable(std::string name);

  std::string getName();
  void setName(std::string name);
protected:
  std::string _name;
};
} // namespace ankicpp
