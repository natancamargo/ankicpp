#include "note/note-type-repository.h"
#include "database/database.h"
#include <soci/sqlite3/soci-sqlite3.h>
#include <soci/use.h>
#include <string>

namespace ankicpp {
// std::tuple<std::vector<NoteTypeDTO>, bool> FieldRepository::read() const {
// return
// {}; } std::tuple<NoteTypeDTO, bool> FieldRepository::readById(std::int64_t
// key) const { return {}; }

bool Repository<NoteTypeDTO, std::int64_t>::create(
    NoteTypeDTO noteTypeDTO) const {
  return database::safeSql([&noteTypeDTO]() {
    database::sql.begin();
    soci::blob blob(ankicpp::database::sql);
    blob.write_from_start(noteTypeDTO.config.data(), noteTypeDTO.config.size());
    database::sql << R"(
INSERT INTO noteTypes(id, name, mtime_secs, usn, config)
VALUES(:id, :name, :mtime_secs, :usn, :config);
)",
        soci::use(noteTypeDTO), use(blob, "config");
    database::sql.commit();
  });
}
// bool FieldRepository::update(NoteTypeDTO noteTypeDTO) const { return {}; }
// bool FieldRepository::del(NoteTypeDTO noteTypeDTO) const { return {}; }
} // namespace ankicpp
namespace soci {
template <> struct type_conversion<ankicpp::NoteTypeDTO> {
  typedef values base_type;

  static void from_base(values const &v, indicator,
                        ankicpp::NoteTypeDTO &noteTypeDTO) {
    noteTypeDTO.id = v.get<std::int64_t>("id");
    noteTypeDTO.name = v.get<std::string>("name");
    noteTypeDTO.mtime_secs = v.get<std::int64_t>("mtime_secs");
    noteTypeDTO.usn = v.get<std::int64_t>("usn");
  }

  static void to_base(const ankicpp::NoteTypeDTO &noteTypeDTO, values &v,
                      indicator &ind) {
    v.set("id", noteTypeDTO.id);
    v.set("name", noteTypeDTO.name);
    v.set("mtime_secs", noteTypeDTO.mtime_secs);
    v.set("usn", noteTypeDTO.usn);

    ind = i_ok;
  }
};
} // namespace soci
