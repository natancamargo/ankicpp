#pragma once

#include "deck/deck-dto.h"
#include "deck/deck.h"
namespace ankicpp {
namespace deckMapper {
DeckDTO modelToDTO(Deck &model);
Deck modelFromDTO(DeckDTO &dto);
} // namespace deckMapper
} // namespace ankicpp
