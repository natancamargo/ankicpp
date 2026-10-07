#include "note/note-repository.h"
#include "database/database.h"
#include <soci/sqlite3/soci-sqlite3.h>
#include <soci/use.h>

namespace ankicpp {
// std::tuple<std::vector<NoteDTO>, bool> NoteRepository::read() const { return
// {}; } std::tuple<NoteDTO, bool> NoteRepository::readById(std::int64_t key)
// const { return {}; }

bool Repository<NoteDTO, std::int64_t>::create(NoteDTO noteDTO) const {
  return database::safeSql([&noteDTO]() {
    database::sql.begin();
    database::sql << R"(
INSERT INTO notes(id, guid, mid, mod, usn, tags, flds, sfld, csum, flags, data)
VALUES(:id, :guid, :mid, :mod, :usn, :tags, :flds, :sfld, :csum, :flags, :data);
)",
        soci::use(noteDTO);
    database::sql.commit();
  });
}
// bool NoteRepository::update(NoteDTO noteDTO) const { return {}; }
// bool NoteRepository::del(NoteDTO noteDTO) const { return {}; }
} // namespace ankicpp
namespace soci {
template <> struct type_conversion<ankicpp::NoteDTO> {
  typedef values base_type;

  static void from_base(values const &v, indicator, ankicpp::NoteDTO &noteDTO) {
    noteDTO.id = v.get<std::int64_t>("id");
    noteDTO.guid = v.get<std::string>("guid");
    noteDTO.mid = v.get<std::int64_t>("mid");
    noteDTO.mod = v.get<std::int64_t>("mod");
    noteDTO.usn = v.get<std::int64_t>("usn");
    noteDTO.tags = v.get<std::string>("tags");
    noteDTO.flds = v.get<std::string>("flds");
    noteDTO.sfld = v.get<std::string>("sfld");
    noteDTO.csum = v.get<std::int64_t>("csum");
    noteDTO.flags = v.get<std::int64_t>("flags");
    noteDTO.data = v.get<std::string>("data");
  }

  static void to_base(const ankicpp::NoteDTO &noteDTO, values &v,
                      indicator &ind) {
    v.set("id", noteDTO.id);
    v.set("guid", noteDTO.guid);
    v.set("mid", noteDTO.mid);
    v.set("mod", noteDTO.mod);
    v.set("usn", noteDTO.usn);
    v.set("tags", noteDTO.tags);
    v.set("flds", noteDTO.flds);
    v.set("sfld", noteDTO.sfld);
    v.set("csum", noteDTO.csum);
    v.set("flags", noteDTO.flags);
    v.set("data", noteDTO.data);

    ind = i_ok;
  }
};
} // namespace soci
