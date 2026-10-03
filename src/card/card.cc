#include "card/card.h"

namespace ankicpp {
std::shared_ptr<Deck> Card::getDeck() const { return _deck; }
void Card::setDeck(std::shared_ptr<Deck> deck) { _deck = deck; }

std::shared_ptr<Template> Card::getTemplate() const { return _template; }
void Card::setTemplate(std::shared_ptr<Template> templatee) {
  _template = templatee;
}

std::shared_ptr<Note> Card::getNote() const { return _note; }
void Card::setNote(std::shared_ptr<Note> note) { _note = note; }
} // namespace ankicpp
