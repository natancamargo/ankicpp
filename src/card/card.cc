#include "card/card.h"

namespace ankicpp {
std::uint32_t Card::getId() const { return _id; }
void Card::setId(std::uint32_t id) { _id = id; }

Deck *Card::getDeck() const { return _deck; }
void Card::setDeck(Deck *deck) { _deck = deck; }

Template *Card::getTemplate() const { return _template; }
void Card::setTemplate(Template *templatee) { _template = templatee; }

Note *Card::getNote() const { return _note; }
void Card::setNote(Note *note) { _note = note; }

bool Card::operator==(const Card &rhs) { return getId() == rhs.getId(); }
bool Card::operator!=(const Card &rhs) { return !(*this == rhs); }
bool Card::operator<(const Card &rhs) { return getId() < rhs.getId(); }
} // namespace ankicpp
