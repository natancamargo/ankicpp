#include <cstdint>
#include <string>
#include <vector>
namespace ankicpp {
class DeckDTO {
public:
  uint32_t id;
  std::string name;
  uint32_t mtime_secs;
  uint32_t usn;
  std::vector<unsigned char> common;
  std::vector<unsigned char> kind;
};
} // namespace ankicpp
