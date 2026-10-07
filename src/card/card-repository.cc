#include "card/card-repository.h"
#include "database/database.h"
#include <soci/sqlite3/soci-sqlite3.h>
#include <soci/use.h>

namespace ankicpp {
// std::tuple<std::vector<CardDTO>, bool> CardRepository::read() const { return
// {}; } std::tuple<CardDTO, bool> CardRepository::readById(std::int64_t key)
// const { return {}; }

bool Repository<CardDTO, std::int64_t>::create(CardDTO cardDTO) const {
  return database::safeSql([&cardDTO]() {
    database::sql.begin();
    database::sql << R"(
INSERT INTO cards(id,nid,did,ord,mod,usn,type,queue,due,ivl,factor,reps,lapses,left,odue,odid,flags,data)
VALUES(:id,:nid,:did,:ord,:mod,:usn,:type,:queue,:due,:ivl,:factor,:reps,:lapses,:left,:odue,:odid,:flags,:data);
)",
        soci::use(cardDTO);
    database::sql.commit();
  });
}
// bool CardRepository::update(CardDTO cardDTO) const { return {}; }
// bool CardRepository::del(CardDTO cardDTO) const { return {}; }
} // namespace ankicpp
namespace soci {
template <> struct type_conversion<ankicpp::CardDTO> {
  typedef values base_type;

  static void from_base(values const &v, indicator, ankicpp::CardDTO &cardDTO) {
    cardDTO.id = v.get<std::int64_t>("id");
    cardDTO.nid = v.get<std::int64_t>("nid");
    cardDTO.did = v.get<std::int64_t>("did");
    cardDTO.ord = v.get<std::int64_t>("ord");
    cardDTO.mod = v.get<std::int64_t>("mod");
    cardDTO.usn = v.get<std::int64_t>("usn");
    cardDTO.type = v.get<std::int64_t>("type");
    cardDTO.queue = v.get<std::int64_t>("queue");
    cardDTO.due = v.get<std::int64_t>("due");
    cardDTO.ivl = v.get<std::int64_t>("ivl");
    cardDTO.factor = v.get<std::int64_t>("factor");
    cardDTO.reps = v.get<std::int64_t>("reps");
    cardDTO.lapses = v.get<std::int64_t>("lapses");
    cardDTO.left = v.get<std::int64_t>("left");
    cardDTO.odue = v.get<std::int64_t>("odue");
    cardDTO.odid = v.get<std::int64_t>("odid");
    cardDTO.flags = v.get<std::int64_t>("flags");
    cardDTO.data = v.get<std::string>("data");
  }

  static void to_base(const ankicpp::CardDTO &cardDTO, values &v,
                      indicator &ind) {
    v.set("id", cardDTO.id);
    v.set("nid", cardDTO.nid);
    v.set("did", cardDTO.did);
    v.set("ord", cardDTO.ord);
    v.set("mod", cardDTO.mod);
    v.set("usn", cardDTO.usn);
    v.set("type", cardDTO.type);
    v.set("queue", cardDTO.queue);
    v.set("due", cardDTO.due);
    v.set("ivl", cardDTO.ivl);
    v.set("factor", cardDTO.factor);
    v.set("reps", cardDTO.reps);
    v.set("lapses", cardDTO.lapses);
    v.set("left", cardDTO.left);
    v.set("odue", cardDTO.odue);
    v.set("odid", cardDTO.odid);
    v.set("flags", cardDTO.flags);
    v.set("data", cardDTO.data);

    ind = i_ok;
  }
};
} // namespace soci
