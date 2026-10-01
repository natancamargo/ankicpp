#pragma once

#include <cstdint>

#include "card/card-type.h"
#include "card/card-dto.h"
#include "note/note.h"
#include "util/time.h"

namespace ankicpp {
class Card {
public:
  std::int64_t getId() const;
  void setId(std::int64_t id);

  CardType *getCardType() const;
  void setCardType(CardType *cardType);

  Note *getNote() const;
  void setNote(Note *note);

  bool operator==(const Card &rhs);
  bool operator!=(const Card &rhs);
  bool operator<(const Card &rhs);

private:
  std::int64_t _id = getNow();
  CardType *_cardType;
  Note *_note;
};
} // namespace ankicpp
