#pragma once

#include <cstdint>

#include "template/template.h"
#include "card/card-dto.h"
#include "note/note.h"
#include "util/identifyable.h"

namespace ankicpp {
class Deck;
  class Card: public Identifyable {
public:
  std::shared_ptr<Deck> getDeck() const;
  void setDeck(std::shared_ptr<Deck> deck);
  
  std::shared_ptr<Template> getTemplate() const;
  void setTemplate(std::shared_ptr<Template> cardType);

  std::shared_ptr<Note> getNote() const;
  void setNote(std::shared_ptr<Note> note);
private:
  std::shared_ptr<Deck> _deck;
  std::shared_ptr<Template> _template;
  std::shared_ptr<Note> _note;
};
} // namespace ankicpp
