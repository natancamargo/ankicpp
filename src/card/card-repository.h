#pragma once

#include "card/card-dto.h"
#include "card/card.h"
#include "database/repository.h"
namespace ankicpp {
class CardRepository : public Repository<Card, std::uint32_t, CardDTO> {
public:
  std::vector<Card> read();
  CardDTO readById(std::uint32_t id);
  CardDTO create(CardDTO cardDTO);
  CardDTO update(CardDTO cardDTO);
  CardDTO del(CardDTO cardDTO);

  CardDTO modelToDTO(Card model);
  Card modelFromDTO(CardDTO dto);
};
} // namespace ankicpp
