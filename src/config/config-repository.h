#pragma once

#include "config/config-dto.h"
#include "database/repository.h"
#include <cstdint>
#include <tuple>

namespace ankicpp {
template <> class Repository<ConfigDTO, std::int64_t>;
template <> class Repository<ConfigDTO, std::int64_t> {
public:
  std::tuple<std::vector<ConfigDTO>, bool> read() const;
  std::tuple<ConfigDTO, bool> readById(std::int64_t key) const;
  bool create(ConfigDTO configDTO) const;
  bool update(ConfigDTO configDTO) const;
  bool del(ConfigDTO configDTO) const;
};
class ConfigRepository : public Repository<ConfigDTO,std::int64_t> {};
} // namespace ankicpp
