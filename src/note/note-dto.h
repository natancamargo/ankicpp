#pragma once

#include <cstdint>
#include <string>
namespace ankicpp {
class NoteDTO {
public:
 std::int64_t id;
  std::string guid;
 std::int64_t mid;
 std::int64_t mod;
 std::int64_t usn;
  std::string tags;
  std::string flds;
  std::string sfld;
 std::int64_t csum;
 std::int64_t flags;
  std::string data;
};
} // namespace ankicpp
