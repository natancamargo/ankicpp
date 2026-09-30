#include "card/card.h"

namespace ankicpp {
std::int64_t Card::getId() const { return _id; }
void Card::setId(std::int64_t id) { _id = id; }

CardType *Card::getCardType() const { return _cardType; }
void Card::setCardType(CardType *cardType) { _cardType = cardType; }

Note *Card::getNote() const { return _note; }
void Card::setNote(Note *note) { _note = note; }

bool Card::operator==(const Card &rhs) { return getId() == rhs.getId(); }
bool Card::operator!=(const Card &rhs) { return !(*this == rhs); }
bool Card::operator<(const Card &rhs) { return getId() < rhs.getId(); }
} // namespace ankicpp
