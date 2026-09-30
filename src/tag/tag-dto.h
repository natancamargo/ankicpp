#include <cstdint>
#include <string>
#include <vector>
namespace ankicpp {
class TagDTO {
public:
  std::string tag;
  std::uint32_t usn;
  bool collapsed;
  std::vector<unsigned char> config;
};
} // namespace ankicpp
