#include "deck/deck-config-repository.h"
#include "database/database.h"
#include "deck/deck-config-dto.h"
#include <soci/sqlite3/soci-sqlite3.h>
#include <soci/use.h>

namespace ankicpp {
// std::tuple<std::vector<ColDTO>, bool> ColRepository::read() const { return
// {}; } std::tuple<ColDTO, bool> ColRepository::readById(std::int64_t key)
// const { return {}; }

bool Repository<DeckConfigDTO, std::int64_t>::create(
    DeckConfigDTO deckConfigDTO) const {
  return database::safeSql([&deckConfigDTO]() {
    database::sql.begin();
    soci::blob blob(ankicpp::database::sql);
    blob.write_from_start(deckConfigDTO.config.data(),
                          deckConfigDTO.config.size());
    database::sql << R"(
INSERT INTO deck_config(id, name, mtime_secs, usn, config)
VALUES(:id, :name, :mtime_secs, :usn, :config);
)",
        soci::use(deckConfigDTO), use(blob, "config");
    database::sql.commit();
  });
}
// bool ColRepository::update(ColDTO deckConfigDTO) const { return {}; }
// bool ColRepository::del(ColDTO deckConfigDTO) const { return {}; }
} // namespace ankicpp
namespace soci {
template <> struct type_conversion<ankicpp::DeckConfigDTO> {
  typedef values base_type;

  static void from_base(values const &v, indicator,
                        ankicpp::DeckConfigDTO &deckConfigDTO) {
    deckConfigDTO.id = v.get<std::int64_t>("id");
    deckConfigDTO.name = v.get<std::string>("name");
    deckConfigDTO.mtime_secs = v.get<std::int64_t>("mtime_secs");
    deckConfigDTO.usn = v.get<std::int64_t>("usn");
  }

  static void to_base(const ankicpp::DeckConfigDTO &deckConfigDTO, values &v,
                      indicator &ind) {
    v.set("id", deckConfigDTO.id);
    v.set("name", deckConfigDTO.name);
    v.set("mtime_secs", deckConfigDTO.mtime_secs);
    v.set("usn", deckConfigDTO.usn);

    ind = i_ok;
  }
};
} // namespace soci
