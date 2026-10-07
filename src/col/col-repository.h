#pragma once

#include "col/col-dto.h"
#include "database/repository.h"
#include <cstdint>
#include <tuple>

namespace ankicpp {
template <> class Repository<ColDTO, std::int64_t>;
template <> class Repository<ColDTO, std::int64_t> {
public:
  std::tuple<std::vector<ColDTO>, bool> read() const;
  std::tuple<ColDTO, bool> readById(std::int64_t key) const;
  bool create(ColDTO colDTO) const;
  bool update(ColDTO colDTO) const;
  bool del(ColDTO colDTO) const;
};
class ColRepository : public Repository<ColDTO,std::int64_t> {};
} // namespace ankicpp
