#include "deck/deck.h"
#include "deck/deck-dto.h"
#include "deck/deck.h"
namespace ankicpp {
namespace deckMapper {
DeckDTO modelToDTO(Deck &model) {
  DeckDTO deckDTO;
  deckDTO.id = model.getId();
  deckDTO.name =
    model.getName();
  deckDTO.mtime_secs = 0;
  deckDTO.usn = 0;

  deckDTO.common.insert(deckDTO.common.end(), {0x08, 0x01, 0x10, 0x01 }); // BS SOH DLS SOH
  deckDTO.kind.insert(deckDTO.kind.end(), {0x0a, 0x02, 0x08, 0x01 }); // LF STX BS SOH

  return deckDTO;
}
// Deck modelFromDTO(DeckDTO dto) {
//   return {};
// }
} // namespace deckMapper
} // namespace ankicpp
