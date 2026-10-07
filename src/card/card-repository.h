#pragma once

#include "card/card-dto.h"
#include "card/card.h"
#include "database/repository.h"
#include <cstdint>
#include <tuple>

namespace ankicpp {
template <> class Repository<CardDTO, std::int64_t>;
template <> class Repository<CardDTO, std::int64_t> {
public:
  std::tuple<std::vector<CardDTO>, bool> read() const;
  std::tuple<CardDTO, bool> readById(std::int64_t key) const;
  bool create(CardDTO cardDTO) const;
  bool update(CardDTO cardDTO) const;
  bool del(CardDTO cardDTO) const;
};
class CardRepository : public Repository<CardDTO, std::int64_t> {};
} // namespace ankicpp
