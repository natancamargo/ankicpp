#pragma once

#include "deck/deck-dto.h"
#include "deck/deck.h"
#include "database/repository.h"
#include <cstdint>
#include <tuple>

namespace ankicpp {
template <> class Repository<DeckDTO, std::int64_t>;
template <> class Repository<DeckDTO, std::int64_t> {
public:
  std::tuple<std::vector<DeckDTO>, bool> read() const;
  std::tuple<DeckDTO, bool> readById(std::int64_t key) const;
  bool create(DeckDTO deckDTO) const;
  bool update(DeckDTO deckDTO) const;
  bool del(DeckDTO deckDTO) const;
};
  class DeckRepository : public Repository<DeckDTO, std::int64_t> {};
} // namespace ankicpp
