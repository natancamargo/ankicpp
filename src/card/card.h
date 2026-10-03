#pragma once

#include <cstdint>

#include "template/template.h"
#include "card/card-dto.h"
#include "note/note.h"
#include "util/time.h"

namespace ankicpp {
class Deck;
class Card {
public:
  std::uint32_t getId() const;
  void setId(std::uint32_t id);

  Deck *getDeck() const;
  void setDeck(Deck *deck);
  
  Template *getTemplate() const;
  void setTemplate(Template *cardType);

  Note *getNote() const;
  void setNote(Note *note);

  bool operator==(const Card &rhs);
  bool operator!=(const Card &rhs);
  bool operator<(const Card &rhs);

private:
  std::int64_t _id = getNow();
  Deck *_deck;
  Template *_template;
  Note *_note;
};
} // namespace ankicpp
