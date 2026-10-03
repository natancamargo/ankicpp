#include "deck/deck.h"

namespace ankicpp {
Deck::Deck(std::string name) : _name(name) {}

std::int64_t Deck::getId() const { return _id; }
void Deck::setId(std::int64_t id) { _id = id; }

std::string Deck::getName() const { return _name; }
void Deck::setName(std::string name) { _name = name; }

std::set<Note *> &Deck::getNotes() { return _notes; }
void Deck::addNote(Note *note) { _notes.insert(note); }
void Deck::removeNote(Note *note) { _notes.erase(note); }

std::set<Card *> &Deck::getCards() { return _cards; }
void Deck::addCard(Card *card) { _cards.insert(card); }
void Deck::removeCard(Card *card) { _cards.erase(card); }
void Deck::clearCards() { _cards.clear(); }

void Deck::generateCards() {
  for(Note *note: notes) {
    std::set<Card*> cards = ...;
    clearCards();
    for(Card *card: cards) {
      addCard(card);
    }
  }
}
} // namespace ankicpp
