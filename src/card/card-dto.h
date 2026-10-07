#pragma once

#include <cstdint>
#include <soci/soci.h>
#include <string>

namespace ankicpp {
class CardDTO {
public:
  std::int64_t id;
  std::int64_t nid;
  std::int64_t did;
  std::int64_t ord;
  std::int64_t mod;
  std::int64_t usn;
  std::int64_t type;
  std::int64_t queue;
  std::int64_t due;
  std::int64_t ivl;
  std::int64_t factor;
  std::int64_t reps;
  std::int64_t lapses;
  std::int64_t left;
  std::int64_t odue;
  std::int64_t odid;
  std::int64_t flags;
  std::string data;
};
} // namespace ankicpp
