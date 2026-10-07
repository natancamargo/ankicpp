#include "col/col-repository.h"
#include "database/database.h"
#include <soci/sqlite3/soci-sqlite3.h>
#include <soci/use.h>

namespace ankicpp {
// std::tuple<std::vector<ColDTO>, bool> ColRepository::read() const { return
// {}; } std::tuple<ColDTO, bool> ColRepository::readById(std::int64_t key)
// const { return {}; }

bool Repository<ColDTO, std::int64_t>::create(ColDTO colDTO) const {
  return database::safeSql([&colDTO]() {
    database::sql.begin();
    database::sql << R"(
INSERT INTO col(id, crt, mod, scm, ver, dty, usn, ls, conf, models, decks, dconf, tags)
VALUES(:id, :crt, :mod, :scm, :ver, :dty, :usn, :ls, :conf, :models, :decks, :dconf, :tags);
)",
        soci::use(colDTO);
    database::sql.commit();
  });
}
// bool ColRepository::update(ColDTO colDTO) const { return {}; }
// bool ColRepository::del(ColDTO colDTO) const { return {}; }
} // namespace ankicpp
namespace soci {
template <> struct type_conversion<ankicpp::ColDTO> {
  typedef values base_type;

  static void from_base(values const &v, indicator, ankicpp::ColDTO &colDTO) {
    colDTO.id = v.get<std::int64_t>("id");
    colDTO.crt = v.get<std::int64_t>("crt");
    colDTO.mod = v.get<std::int64_t>("mod");
    colDTO.scm = v.get<std::int64_t>("scm");
    colDTO.ver = v.get<std::int64_t>("ver");
    colDTO.dty = v.get<std::int64_t>("dty");
    colDTO.usn = v.get<std::int64_t>("usn");
    colDTO.ls = v.get<std::int64_t>("ls");
    colDTO.conf = v.get<std::string>("conf");
    colDTO.models = v.get<std::string>("models");
    colDTO.decks = v.get<std::string>("decks");
    colDTO.dconf = v.get<std::string>("dconf");
    colDTO.tags = v.get<std::string>("tags");
  }

  static void to_base(const ankicpp::ColDTO &colDTO, values &v,
                      indicator &ind) {
    v.set("id", colDTO.id);
    v.set("crt", colDTO.crt);
    v.set("mod", colDTO.mod);
    v.set("scm", colDTO.scm);
    v.set("ver", colDTO.ver);
    v.set("dty", colDTO.dty);
    v.set("usn", colDTO.usn);
    v.set("ls", colDTO.ls);
    v.set("conf", colDTO.conf);
    v.set("models", colDTO.models);
    v.set("decks", colDTO.decks);
    v.set("dconf", colDTO.dconf);
    v.set("tags", colDTO.tags);
    ind = i_ok;
  }
};
} // namespace soci
