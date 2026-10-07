#pragma once

#include "note/note-type.h"
#include "note/note-type-dto.h"
#include "database/repository.h"
#include <cstdint>
#include <tuple>

namespace ankicpp {
template <> class Repository<NoteTypeDTO, std::int64_t>;
template <> class Repository<NoteTypeDTO, std::int64_t> {
public:
  std::tuple<std::vector<NoteTypeDTO>, bool> read() const;
  std::tuple<NoteTypeDTO, bool> readById(std::int64_t key) const;
  bool create(NoteTypeDTO noteTypeDTO) const;
  bool update(NoteTypeDTO noteTypeDTO) const;
  bool del(NoteTypeDTO noteTypeDTO) const;
};
class NoteTypeRepository : public Repository<NoteTypeDTO,std::int64_t> {};
} // namespace ankicpp
