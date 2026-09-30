#pragma once

#include <cstdint>
#include <string>

namespace ankicpp {
class Field {
public:
  Field(std::string name);

  std::string getName() const;
  void setName(const std::string &name);

  std::string getDescription() const;
  void setDescription(std::string description);

  std::string getFont() const;
  void setFont(std::string font);

  uint getFontSize() const;
  void setFontSize(uint fontSize);

private:
  std::string _name;
  std::string _description;
  std::string _font;
  uint _fontSize;
};
} // namespace ankicpp
