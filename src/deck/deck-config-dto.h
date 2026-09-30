#include <cstdint>
#include <string>
#include <vector>
namespace ankicpp {
class DeckConfigDTO {
public:
  std::uint32_t id;
  std::string name;
  std::uint32_t mtime_secs;
  std::uint32_t usn;
  std::vector<unsigned char> config;
};
} // namespace ankicpp
