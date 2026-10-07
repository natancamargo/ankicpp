#include "template/template-repository.h"
#include "database/database.h"
#include <cstdint>
#include <soci/blob.h>
#include <soci/sqlite3/soci-sqlite3.h>
#include <soci/use.h>

namespace ankicpp {
// std::tuple<std::vector<TemplateDTO>, bool> TemplateRepository::read() const {
// return
// {}; } std::tuple<TemplateDTO, bool>
// TemplateRepository::readById(std::int64_t key) const { return {}; }

bool Repository<TemplateDTO,std::int64_t>::create(TemplateDTO templateDTO) const {
  return database::safeSql([&templateDTO]() {
    database::sql.begin();
    soci::blob blob(ankicpp::database::sql);
    blob.write_from_start(templateDTO.config.data(), templateDTO.config.size());
    database::sql << R"(
INSERT INTO templates(ntid, ord, name, mtime_secs, usn, config)
VALUES(:ntid, :ord, :name, :mtime_secs, :usn, :config);
)",
        soci::use(templateDTO), use(blob, "config");
    database::sql.commit();
  });
  return true;
}
// bool TemplateRepository::update(TemplateDTO templateDTO) const { return {}; }
// bool TemplateRepository::del(TemplateDTO templateDTO) const { return {}; }
} // namespace ankicpp
namespace soci {
template <> struct type_conversion<ankicpp::TemplateDTO> {
  typedef values base_type;

  static void from_base(values const &v, indicator,
                        ankicpp::TemplateDTO &templateDTO) {
    templateDTO.ntid = v.get<std::int64_t>("ntid");
    templateDTO.ord = v.get<std::int64_t>("ord");
    templateDTO.name = v.get<std::string>("name");
    templateDTO.mtime_secs = v.get<std::int64_t>("mtime_secs");
    templateDTO.usn = v.get<std::int64_t>("usn");
  }

  static void to_base(const ankicpp::TemplateDTO &templateDTO, values &v,
                      indicator &ind) {
    v.set("ntid", templateDTO.ntid);
    v.set("ord", templateDTO.ord);
    v.set("name", templateDTO.name);
    v.set("mtime_secs", templateDTO.mtime_secs);
    v.set("usn", templateDTO.usn);

    ind = i_ok;
  }
};
} // namespace soci
