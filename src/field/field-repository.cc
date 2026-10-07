#include "field/field-repository.h"
#include "database/database.h"
#include <soci/sqlite3/soci-sqlite3.h>
#include <soci/use.h>

namespace ankicpp {
// std::tuple<std::vector<FieldDTO>, bool> FieldRepository::read() const { return
// {}; } std::tuple<FieldDTO, bool> FieldRepository::readById(std::int64_t key)
// const { return {}; }

bool Repository<FieldDTO, std::int64_t>::create(FieldDTO fieldDTO) const {
  return database::safeSql([&fieldDTO]() {
    database::sql.begin();
    soci::blob blob(ankicpp::database::sql);
    blob.write_from_start(fieldDTO.config.data(), fieldDTO.config.size());
    database::sql << R"(
INSERT INTO fields(ntid, ord, name, config)
VALUES(:ntid, :ord, :name, :config);
)",
      soci::use(fieldDTO), use(blob, "config");
    database::sql.commit();
  });
}
// bool FieldRepository::update(FieldDTO fieldDTO) const { return {}; }
// bool FieldRepository::del(FieldDTO fieldDTO) const { return {}; }
} // namespace ankicpp
namespace soci {
template <> struct type_conversion<ankicpp::FieldDTO> {
  typedef values base_type;

  static void from_base(values const &v, indicator, ankicpp::FieldDTO &fieldDTO) {
    fieldDTO.ntid = v.get<std::int64_t>("ntid");
    fieldDTO.ord = v.get<std::int64_t>("ord");
    fieldDTO.name = v.get<std::string>("name");
  }

  static void to_base(const ankicpp::FieldDTO &fieldDTO, values &v,
                      indicator &ind) {
    v.set("ntid", fieldDTO.ntid);
    v.set("ord", fieldDTO.ord);
    v.set("name", fieldDTO.name);

    ind = i_ok;
  }
};
} // namespace soci
