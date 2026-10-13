#pragma once

#include <memory>
#include <set>
#include <string>

#include "card/card.h"
#include "note/note.h"
#include "util/identifyable.h"
#include "util/nameable.h"

namespace ankicpp {
class Deck : public Identifyable,
             public Nameable,
             public std::enable_shared_from_this<Deck> {
public:
  Deck(std::string name);

  std::set<std::shared_ptr<Note>> &getNotes();
  void addNote(std::shared_ptr<Note> note);
  void removeNote(std::shared_ptr<Note> note);

  std::set<std::shared_ptr<Card>> &getCards();
  void addCard(std::shared_ptr<Card> card);
  void removeCard(std::shared_ptr<Card> card);
  void clearCards();

  const std::set<std::shared_ptr<Deck>> &getDecks();
  void setDecks(const std::set<std::shared_ptr<Deck>> &decks);
  void addDeck(std::shared_ptr<Deck> &deck);
  void removeDeck(std::shared_ptr<Deck> &deck);

  const std::weak_ptr<Deck> &getParent();
  void setParent(const std::weak_ptr<Deck> &deck);

  bool generateCards();

private:
  std::set<std::shared_ptr<Note>> _notes;
  std::set<std::shared_ptr<Card>> _cards;

  std::set<std::shared_ptr<Deck>> _decks;
  std::weak_ptr<Deck> _parent;
};
} // namespace ankicpp
