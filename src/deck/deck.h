#pragma once

#include <memory>
#include <set>
#include <string>

#include "card/card.h"
#include "deck/deck-config-dto.h"
#include "deck/deck-dto.h"
#include "note/note.h"
#include "util/identifyable.h"
#include "util/nameable.h"

namespace ankicpp {
  class Deck: public Identifyable, public Nameable {
public:
  Deck(std::string name);

  std::set<std::shared_ptr<Note>> &getNotes();
  void addNote(std::shared_ptr<Note> note);
  void removeNote(std::shared_ptr<Note> note);

  std::set<std::shared_ptr<Card>> &getCards();
  void addCard(std::shared_ptr<Card> card);
  void removeCard(std::shared_ptr<Card> card);
  void clearCards();

  void generateCards();

private:
  std::set<std::shared_ptr<Note>> _notes;
  std::set<std::shared_ptr<Card>> _cards;
};
} // namespace ankicpp
