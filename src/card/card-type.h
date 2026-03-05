#pragma once

#include <string>

namespace ankicpp {
  class CardType {
  public:
    std::string getName() const;
    void setName(std::string name);

    std::string getFrontTemplate() const;
    void setFrontTemplate(std::string frontTemplate);

    std::string getBackTemplate() const;
    void setBackTemplate(std::string backTemplate);
  private:
    std::string _name;
    std::string _frontTemplate;
    std::string _backTemplate;
  };
}
