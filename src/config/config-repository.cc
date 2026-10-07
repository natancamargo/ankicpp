#include "config/config-repository.h"
#include "database/database.h"
#include <soci/sqlite3/soci-sqlite3.h>
#include <soci/use.h>

namespace ankicpp {
// std::tuple<std::vector<ConfigDTO>, bool> ConfigRepository::read() const {
// return
// {}; } std::tuple<ConfigDTO, bool> ConfigRepository::readById(std::int64_t
// key) const { return {}; }

bool Repository<ConfigDTO, std::int64_t>::create(ConfigDTO configDTO) const {
  return database::safeSql([&configDTO]() {
    database::sql.begin();
    soci::blob blob(ankicpp::database::sql);
    blob.write_from_start(configDTO.val.data(), configDTO.val.size());
    database::sql << R"(
INSERT INTO config(KEY, usn, mtime_secs, val)
VALUES(:KEY, :usn, :mtime_secs, :val);
)",
        soci::use(configDTO), use(blob, "val");
    database::sql.commit();
  });
}
// bool ConfigRepository::update(ConfigDTO configDTO) const { return {}; }
// bool ConfigRepository::del(ConfigDTO configDTO) const { return {}; }
} // namespace ankicpp
namespace soci {
template <> struct type_conversion<ankicpp::ConfigDTO> {
  typedef values base_type;

  static void from_base(values const &v, indicator,
                        ankicpp::ConfigDTO &configDTO) {
    configDTO.KEY = v.get<std::string>("KEY");
    configDTO.usn = v.get<std::int64_t>("usn");
    configDTO.mtime_secs = v.get<std::int64_t>("mtime_secs");
  }

  static void to_base(const ankicpp::ConfigDTO &configDTO, values &v,
                      indicator &ind) {
    v.set("KEY", configDTO.KEY);
    v.set("usn", configDTO.usn);
    v.set("mtime_secs", configDTO.mtime_secs);

    ind = i_ok;
  }
};
} // namespace soci
