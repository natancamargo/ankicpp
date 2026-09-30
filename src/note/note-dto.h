#include <cstdint>
#include <string>
namespace ankicpp {
class NoteDTO {
public:
  uint32_t id;
  std::string guid;
  uint32_t mid;
  uint32_t mod;
  uint32_t usn;
  std::string tags;
  std::string flds;
  uint32_t sfld;
  uint32_t csum;
  uint32_t flags;
  std::string datai;
};
} // namespace ankicpp
