#pragma once

#include <list>
#include <string>
#include <algorithm>
#include <cstdint>
#include <memory>

#include "card/card-type.h"
#include "field/field.h"
#include "util/time.h"

namespace ankicpp {
  class NoteType {
  public:
    NoteType(std::string name);

    std::int64_t getId() const;
    void setId(std::int64_t id);

    std::string getName() const;
    void setName(std::string name);

    std::list<CardType*> &getCardTypes();
    void addCardType(CardType *cardType);
    void removeCardType(CardType *cardType);

    std::list<Field*> &getFields();
    void addField(Field *field);
    void removeField(Field *field);

    std::string getHeader() const;
    void setHeader(std::string header);

    std::string getFooter() const;
    void setFooter(std::string footer);

    std::string getStyle() const;
    void setStyle(std::string style);
  private:
    std::int64_t _id = getNow();
    std::string _name;
    std::list<CardType*> _cardTypes;
    std::list<Field*> _fields;
    std::string _header;
    std::string _footer;
    std::string _style;
  };

  extern std::shared_ptr<NoteType> BasicNoteTypePtr;
  extern std::shared_ptr<NoteType> ClozeNoteTypePtr;
  extern NoteType *BasicNoteType;
  extern NoteType *ClozeNoteType;

}
