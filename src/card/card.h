#pragma once

#include <cstdint>

#include "card/card-dto.h"
#include "template/template.h"
#include "template/template-repository.h"
#include "note/note.h"
#include "util/identifyable.h"

namespace ankicpp {
class Deck;
  class Card: public Identifyable {
public:
  std::shared_ptr<Deck> getDeck() const;
  void setDeck(std::shared_ptr<Deck> deck);
  
  uint64_t getOrder() const;
  void setOrder(uint64_t order);

  std::shared_ptr<Note> getNote() const;
  void setNote(std::shared_ptr<Note> note);
private:
  std::shared_ptr<Deck> _deck;
  int64_t _order;
  std::shared_ptr<Note> _note;
};
} // namespace ankicpp
