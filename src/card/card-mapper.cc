#include "card/card-dto.h"
#include "card/card.h"
#include "deck/deck.h"
#include <iostream>
namespace ankicpp {
namespace cardMapper {
CardDTO modelToDTO(Card &model) {
  CardDTO cardDTO;
  
  cardDTO.id = model.getNote()->getId();
  cardDTO.nid = model.getNote()->getId();
  cardDTO.did = model.getDeck()->getId();
  cardDTO.ord =
      model.getNote()->getType()->getTemplateIndex(model.getTemplate());
  cardDTO.mod = 0;
  cardDTO.usn = 0;
  cardDTO.type = 0;
  cardDTO.queue = 0;
  cardDTO.due = 0;
  cardDTO.ivl = 0;
  cardDTO.factor = 0;
  cardDTO.reps = 0;
  cardDTO.lapses = 0;
  cardDTO.left = 0;
  cardDTO.odue = 0;
  cardDTO.odid = 0;
  cardDTO.flags = 0;
  cardDTO.data = "{}";
  return cardDTO;
}
// Card modelFromDTO(CardDTO dto) {
//   return {};
// }
} // namespace cardMapper
} // namespace ankicpp
