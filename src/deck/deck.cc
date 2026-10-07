#include "deck/deck.h"
#include "util/nameable.h"
#include <memory>

namespace ankicpp {
Deck::Deck(std::string name) : Nameable(name) {}

std::set<std::shared_ptr<Note>> &Deck::getNotes() { return _notes; }
void Deck::addNote(std::shared_ptr<Note> note) { _notes.insert(note); }
void Deck::removeNote(std::shared_ptr<Note> note) { _notes.erase(note); }

std::set<std::shared_ptr<Card>> &Deck::getCards() { return _cards; }
void Deck::addCard(std::shared_ptr<Card> card) {
  _cards.insert(card);
  card->setDeck(std::make_shared<Deck>(*this));
}
void Deck::removeCard(std::shared_ptr<Card> card) {
  _cards.erase(card);
  card->setDeck(nullptr);
}
void Deck::clearCards() { _cards.clear(); }

void Deck::generateCards() {
  const std::set<std::shared_ptr<Note>> &notes = getNotes();
  for (std::shared_ptr<Note> note : notes) {
    const std::shared_ptr<NoteType> &noteType = note->getType();
    for (const std::shared_ptr<Template> &templatee :
         noteType->getTemplates()) {
      const std::shared_ptr<Card> &card = std::make_shared<Card>();
      card->setId(note->getId());
      card->setNote(note);
      card->setTemplate(templatee);
      addCard(card);
    }
  }
}
} // namespace ankicpp
