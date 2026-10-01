#pragma once

#include <cstdint>
#include <string>
namespace ankicpp {
class ColDTO {
public:
  std::uint32_t id;
  std::uint32_t crt;
  std::uint32_t mod;
  std::uint32_t scm;
  std::uint32_t ver;
  std::uint32_t dty;
  std::uint32_t usn;
  std::uint32_t ls;
  std::string conf;
  std::string models;
  std::string decks;
  std::string dconf;
  std::string tags;
};
} // namespace ankicpp
