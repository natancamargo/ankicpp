#include <cstdint>
namespace ankicpp {
class NoteTypeDTO {
public:
  std::uint32_t id;
  std::uint32_t cid;
  std::uint32_t usn;
  std::uint32_t ease;
  std::uint32_t ivl;
  std::uint32_t lastIvl;
  std::uint32_t factor;
  std::uint32_t time;
  std::uint32_t type;
};
} // namespace ankicpp
