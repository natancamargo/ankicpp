#include "card/card.h"

namespace ankicpp {
std::shared_ptr<Deck> Card::getDeck() const { return _deck; }
void Card::setDeck(std::shared_ptr<Deck> deck) { _deck = deck; }

uint64_t Card::getOrder() const { return _order; }
void Card::setOrder(uint64_t order) { _order = order; }

std::shared_ptr<Note> Card::getNote() const { return _note; }
void Card::setNote(std::shared_ptr<Note> note) { _note = note; }
} // namespace ankicpp
