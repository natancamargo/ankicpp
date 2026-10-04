#include "card/card-repository.h"

namespace ankicpp {
std::vector<Card> CardRepository::read() { return {}; }
CardDTO CardRepository::readById(std::uint32_t id) { return {}; }
CardDTO CardRepository::create(CardDTO cardDTO) { return {}; }
CardDTO CardRepository::update(CardDTO cardDTO) { return {}; }
CardDTO CardRepository::del(CardDTO cardDTO) { return {}; }

CardDTO CardRepository::modelToDTO(Card model) {
  CardDTO cardDTO;

  cardDTO.id = model.getNote()->getId();
  cardDTO.nid = model.getNote()->getId();
  cardDTO.ord =
      model.getNote()->getType()->getTemplateIndex(model.getTemplate());
  cardDTO.mod = getNow();
  cardDTO.usn = -1;
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
  return {};
}
Card CardRepository::modelFromDTO(CardDTO dto) { return {}; }
} // namespace ankicpp
