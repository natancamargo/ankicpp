#pragma once

#include "deck/deck.h"
#include <string_view>
namespace ankicpp {
enum class ExportError {
  NO_ERROR,
  UNKNOWN_ERROR,
  OPENING_ERROR,  
  WRITING_ERROR,  
  EMPTY_DECK_ERROR,
  INVALID_NOTE_ERROR,
  INVALID_NOTE_TYPE_ERROR
};
extern ExportError exportError;

bool exportDeck(Deck deck, std::string_view filename);
} // namespace ankicpp
