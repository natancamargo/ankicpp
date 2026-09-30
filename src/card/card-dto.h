#include <cstdint>
#include <string>

namespace ankicpp {
class CardDTO {
public:
  std::uint32_t id;
  std::uint32_t nid;
  std::uint32_t did;
  std::uint32_t ord;
  std::uint32_t mod;
  std::uint32_t usn;
  std::uint32_t type;
  std::uint32_t queue;
  std::uint32_t due;
  std::uint32_t ivl;
  std::uint32_t factor;
  std::uint32_t reps;
  std::uint32_t lapses;
  std::uint32_t left;
  std::uint32_t odue;
  std::uint32_t odid;
  std::uint32_t flags;
  std::string data;
};
} // namespace ankicpp
