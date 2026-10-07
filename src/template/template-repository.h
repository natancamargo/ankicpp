#pragma once

#include "database/repository.h"
#include "template/template-dto.h"
#include <tuple>

namespace ankicpp {

template <> class Repository<TemplateDTO, std::int64_t>;

template <> class Repository<TemplateDTO, std::int64_t> {
public:
  std::tuple<std::vector<TemplateDTO>, bool> read() const;
  std::tuple<TemplateDTO, bool> readById(std::int64_t key) const;
  bool create(TemplateDTO templateDTO) const;
  bool update(TemplateDTO templateDTO) const;
  bool del(TemplateDTO templateDTO) const;
};

class TemplateRepository : public Repository<TemplateDTO, std::int64_t> {};

} // namespace ankicpp
