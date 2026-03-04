#pragma once

#include <string>
#include <cstdint>

namespace ankicpp {
  class Field {
  public:
    Field() = default;
    Field(std::string name);

    std::string getName();
    void setName(const std::string &name);

    std::string getDescription();
    void setDescription(std::string description);

    std::string getFont();
    void setFont(std::string font);

    uint getFontSize();
    void setFontSize(uint fontSize);
  private:
    std::string _name;
    std::string _description;
    std::string _font;
    uint _fontSize;
  };
}
