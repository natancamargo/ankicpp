#pragma once

#include <string>
#include <cstdint>

#include "util/time.h"
#include "card/card-type.h"
#include "note/note.h"

namespace ankicpp {
  class Card {
  public:
    std::int64_t getId() const;
    void setId(std::int64_t id);

    CardType *getCardType() const;
    void setCardType(CardType *cardType);

    Note* getNote() const;
    void setNote(Note *note);

    bool operator==(const Card &rhs);
    bool operator!=(const Card &rhs);
    bool operator<(const Card &rhs);
  private:
    std::int64_t _id = getNow();
    CardType *_cardType;
    Note *_note;
  };
}
