#pragma once

#include <cstdint>
#include <string>
#include <vector>
namespace ankicpp {
class DeckDTO {
public:
  std::int64_t id;
  std::string name;
  std::int64_t mtime_secs;
  std::int64_t usn;
  std::vector<unsigned char> common;
  std::vector<unsigned char> kind;

  static DeckDTO createDefaultDTO() {
    DeckDTO deckDTO;
    deckDTO.id = 1;
    deckDTO.name = "Default";
    deckDTO.mtime_secs = 0;
    deckDTO.usn = 0;

    deckDTO.common.insert(deckDTO.common.end(), {0x08, 0x01, 0x10, 0x01});
    deckDTO.kind.insert(deckDTO.kind.end(), {0x0a, 0x02, 0x08, 0x01});
    return deckDTO;
  }
};
} // namespace ankicpp
