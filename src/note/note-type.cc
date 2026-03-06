#include "note/note-type.h"

namespace ankicpp {
  NoteType::NoteType(std::string name) : _name(name) {}

  std::int64_t NoteType::getId() const {
    return _id;
  }
  void NoteType::setId(std::int64_t id) {
    _id = id;
  }

  std::string NoteType::getName() const {
    return _name;
  }
  void NoteType::setName(std::string name) {
    _name = name;
  }

  std::list<CardType*> &NoteType::getCardTypes() {
    return _cardTypes;
  }
  void NoteType::addCardType(CardType *cardType) {
    auto it = std::find_if(_cardTypes.begin(), _cardTypes.end(),
                           [cardType](CardType *_cardType) {
                             return cardType == _cardType;
                           });
    if (it == _cardTypes.end()) {
      _cardTypes.push_back(cardType);
    }
  }
  void NoteType::removeCardType(CardType *cardType) {
    _cardTypes.remove(cardType);
  }

  std::list<Field*> &NoteType::getFields() {
    return _fields;
  }
  void NoteType::addField(Field *field) {
    auto it = std::find_if(_fields.begin(), _fields.end(), [field](Field *_field){
      return field == _field;
    });
    if (it == _fields.end()) {
      _fields.push_back(field);
    }
  }
  void NoteType::removeField(Field *field) {
    _fields.remove(field);
  }

  std::string NoteType::getHeader() const {
    return _header;
  }
  void NoteType::setHeader(std::string header) {
    _header = header;
  }

  std::string NoteType::getFooter() const {
    return _footer;
  }
  void NoteType::setFooter(std::string footer) {
    _footer = footer;
  }

  std::string NoteType::getStyle() const {
    return _style;
  }
  void NoteType::setStyle(std::string style) {
    _style = style;
  }
}
