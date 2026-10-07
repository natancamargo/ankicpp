#pragma once

#include "field/field-dto.h"
#include "field/field.h"
#include "database/repository.h"
#include <cstdint>
#include <tuple>

namespace ankicpp {
template <> class Repository<FieldDTO, std::int64_t>;
template <> class Repository<FieldDTO, std::int64_t> {
public:
  std::tuple<std::vector<FieldDTO>, bool> read() const;
  std::tuple<FieldDTO, bool> readById(std::int64_t key) const;
  bool create(FieldDTO fieldDTO) const;
  bool update(FieldDTO fieldDTO) const;
  bool del(FieldDTO fieldDTO) const;
};
class FieldRepository : public Repository<FieldDTO,std::int64_t> {};
} // namespace ankicpp
