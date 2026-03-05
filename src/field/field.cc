#include "field/field.h"

namespace ankicpp {
  Field::Field(std::string name) : _name(name) {}

  std::string Field::getName() const {
    return _name;
  }
  void Field::setName(const std::string &name) {
    _name = name;
  }

  std::string Field::getDescription() const {
    return _description;
  }
  void Field::setDescription(std::string description) {
    _description = description;
  }

  std::string Field::getFont() const {
    return _font;
  }
  void Field::setFont(std::string font) {
    _font = font;
  }

  uint Field::getFontSize() const {
    return _fontSize;
  }
  void Field::setFontSize(uint fontSize) {
    _fontSize = fontSize;
  }
}
