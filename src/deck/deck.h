#pragma once

#include <cstdint>
#include <set>
#include <string>

#include "deck/deck-config-dto.h"
#include "deck/deck-dto.h"
#include "card/card.h"
#include "note/note.h"
#include "util/time.h"

namespace ankicpp {
class Deck {
public:
  Deck(std::string name);

  std::int64_t getId() const;
  void setId(std::int64_t id);

  std::string getName() const;
  void setName(std::string name);

  std::set<Note *> &getNotes();
  void addNote(Note *note);
  void removeNote(Note *note);

  std::set<Card *> &getCards();
  void addCard(Card *card);
  void removeCard(Card *card);
  void clearCards();

  void generateCards();

private:
  std::int64_t _id = getNow();
  std::string _name;
  std::set<Note *> _notes;
  std::set<Card *> _cards;
};
} // namespace ankicpp
