#include <cstdint>
#include <string>
#include <vector>
namespace ankicpp {
class TemplateDTO {
public:
  uint32_t ntid;
  uint32_t ord;
  std::string name;
  uint32_t mtime_secs;
  uint32_t usn;
  std::vector<unsigned char> config;
};
} // namespace ankicpp
