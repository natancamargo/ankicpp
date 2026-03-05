#include "card/card-type.h"

namespace ankicpp {
  std::string CardType::getName() const {
    return _name;
  }
  void CardType::setName(std::string name) {
    _name = name;
  }

  std::string CardType::getFrontTemplate() const {
    return _frontTemplate;
  }
  void CardType::setFrontTemplate(std::string frontTemplate) {
    _frontTemplate = frontTemplate;
  }

  std::string CardType::getBackTemplate() const {
    return _backTemplate;
  }
  void CardType::setBackTemplate(std::string backTemplate) {
    _backTemplate = backTemplate;
  }
}
