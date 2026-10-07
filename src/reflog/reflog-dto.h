#pragma once

#include <cstdint>
namespace ankicpp {
class NoteTypeDTO {
public:
  std::int64_t id;
  std::int64_t cid;
  std::int64_t usn;
  std::int64_t ease;
  std::int64_t ivl;
  std::int64_t lastIvl;
  std::int64_t factor;
  std::int64_t time;
  std::int64_t type;
};
} // namespace ankicpp
