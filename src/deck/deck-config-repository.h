#pragma once

#include "deck/deck-config-dto.h"
#include "database/repository.h"
#include <cstdint>
#include <tuple>

namespace ankicpp {
template <> class Repository<DeckConfigDTO, std::int64_t>;
template <> class Repository<DeckConfigDTO, std::int64_t> {
public:
  std::tuple<std::vector<DeckConfigDTO>, bool> read() const;
  std::tuple<DeckConfigDTO, bool> readById(std::int64_t key) const;
  bool create(DeckConfigDTO deckConfigDTO) const;
  bool update(DeckConfigDTO deckConfigDTO) const;
  bool del(DeckConfigDTO deckConfigDTO) const;
};
class DeckConfigRepository : public Repository<DeckConfigDTO,std::int64_t> {};
} // namespace ankicpp
