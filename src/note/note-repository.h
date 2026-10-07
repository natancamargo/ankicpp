#pragma once

#include "note/note-dto.h"
#include "note/note.h"
#include "database/repository.h"
#include <cstdint>
#include <tuple>

namespace ankicpp {
template <> class Repository<NoteDTO, std::int64_t>;
template <> class Repository<NoteDTO, std::int64_t> {
public:
  std::tuple<std::vector<NoteDTO>, bool> read() const;
  std::tuple<NoteDTO, bool> readById(std::int64_t key) const;
  bool create(NoteDTO noteDTO) const;
  bool update(NoteDTO noteDTO) const;
  bool del(NoteDTO noteDTO) const;
};
class NoteRepository : public Repository<NoteDTO,std::int64_t> {};
} // namespace ankicpp
