#include "card/card-repository.h"

namespace ankicpp {
std::vector<Card> CardRepository::read() { return {}; }
CardDTO CardRepository::readById(std::uint32_t id) { return {}; }
CardDTO CardRepository::create(CardDTO cardDTO) { return {}; }
CardDTO CardRepository::update(CardDTO cardDTO) { return {}; }
CardDTO CardRepository::del(CardDTO cardDTO) { return {}; }

CardDTO CardRepository::modelToDTO(Card model) { return {}; }
Card CardRepository::modelFromDTO(CardDTO dto) { return {}; }
} // namespace ankicpp
