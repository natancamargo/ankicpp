#include "deck/deck-repository.h"
#include "database/database.h"
#include <soci/sqlite3/soci-sqlite3.h>
#include <soci/use.h>

namespace ankicpp {
// std::tuple<std::vector<DeckDTO>, bool> DeckRepository::read() const { return
// {}; } std::tuple<DeckDTO, bool> DeckRepository::readById(std::int64_t key)
// const { return {}; }

bool Repository<DeckDTO, std::int64_t>::create(DeckDTO deckDTO) const {
  return database::safeSql([&deckDTO]() {
    database::sql.begin();
    soci::blob common(ankicpp::database::sql);
    soci::blob kind(ankicpp::database::sql);
    common.write_from_start(deckDTO.common.data(), deckDTO.common.size());
    kind.write_from_start(deckDTO.kind.data(), deckDTO.kind.size());
    database::sql << R"(
INSERT INTO decks(id, name, mtime_secs, usn, common, kind)
VALUES(:id, :name, :mtime_secs, :usn, :common, :kind);
)",
        soci::use(deckDTO), use(common, "common"), use(kind, "kind");
    database::sql.commit();
  });
}
// bool DeckRepository::update(DeckDTO deckDTO) const { return {}; }
// bool DeckRepository::del(DeckDTO deckDTO) const { return {}; }
} // namespace ankicpp
namespace soci {
template <> struct type_conversion<ankicpp::DeckDTO> {
  typedef values base_type;

  static void from_base(values const &v, indicator, ankicpp::DeckDTO &deckDTO) {
    deckDTO.id = v.get<std::int64_t>("id");
    deckDTO.name = v.get<std::string>("name");
    deckDTO.mtime_secs = v.get<std::int64_t>("mtime_secs");
    deckDTO.usn = v.get<std::int64_t>("usn");
  }

  static void to_base(const ankicpp::DeckDTO &deckDTO, values &v,
                      indicator &ind) {
    v.set("id", deckDTO.id);
    v.set("name", deckDTO.name);
    v.set("mtime_secs", deckDTO.mtime_secs);
    v.set("usn", deckDTO.usn);

    ind = i_ok;
  }
};
} // namespace soci
