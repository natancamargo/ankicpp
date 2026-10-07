#pragma once

#include "card/card-dto.h"
#include "card/card.h"
namespace ankicpp {
namespace cardMapper {
CardDTO modelToDTO(Card &model);
Card modelFromDTO(CardDTO &dto);
} // namespace cardMapper
} // namespace ankicpp
