#pragma once

#include "util/identifyable.h"
#include <cstdint>
#include <string>
namespace ankicpp {
class ColDTO {
public:
  std::int64_t id;
  std::int64_t crt;
  std::int64_t mod;
  std::int64_t scm;
  std::int64_t ver;
  std::int64_t dty;
  std::int64_t usn;
  std::int64_t ls;
  std::string conf;
  std::string models;
  std::string decks;
  std::string dconf;
  std::string tags;

  static ColDTO createDTO() {
    ColDTO colDTO;
    colDTO.id = Identifyable::generateRandomId();
    colDTO.crt = 0;
    colDTO.mod = 0;
    colDTO.scm = 0;
    colDTO.ver = 18;
    colDTO.dty = 0;
    colDTO.usn = 0;
    colDTO.ls = 0;
    colDTO.conf = "";
    colDTO.models = "";
    colDTO.decks  = "";
    colDTO.dconf = "";
    colDTO.tags = "";

    return colDTO;
  }
};
} // namespace ankicpp
