#include "deck/deck.h"
#include "note/note-type-dto.h"
#include "note/note-type.h"
#include "resources/proto/note-type.pb.h"

namespace ankicpp {
namespace noteTypeMapper {
NoteTypeDTO modelToDTO(NoteType &model) {
  NoteTypeDTO noteTypeDTO;
  noteTypeDTO.id = model.getId();
  noteTypeDTO.name = model.getName();
  noteTypeDTO.mtime_secs = 0;
  noteTypeDTO.usn = 0;

  anki::Notetype::Config config;

  if (model == *clozeNoteType) {
    config.set_kind(
        anki::Notetype_Config_Kind::Notetype_Config_Kind_KIND_CLOZE);
    config.set_original_stock_kind(
        anki::StockNotetype_OriginalStockKind::
            StockNotetype_OriginalStockKind_ORIGINAL_STOCK_KIND_CLOZE);

  } else {
    config.set_kind(
        anki::Notetype_Config_Kind::Notetype_Config_Kind_KIND_NORMAL);
    config.set_original_stock_kind(
        anki::StockNotetype_OriginalStockKind::
            StockNotetype_OriginalStockKind_ORIGINAL_STOCK_KIND_BASIC);
  }

  const std::string &header = model.getHeader();
  const std::string &footer = model.getFooter();
  const std::string &style = model.getStyle();
  config.set_css(style);
  config.set_latex_pre(header);
  config.set_latex_post(footer);

  anki::Notetype_Config_CardRequirement *cardRequirement = config.add_reqs();
  cardRequirement->set_kind(anki::Notetype_Config_CardRequirement_Kind::
                                Notetype_Config_CardRequirement_Kind_KIND_ANY);
  cardRequirement->add_field_ords(0);  

  const std::string configSerialized = config.SerializeAsString();
  std::copy(configSerialized.begin(), configSerialized.end(),
            std::back_inserter(noteTypeDTO.config));

  return noteTypeDTO;
}
// NoteType modelFromDTO(NoteTypeDTO dto) {
//   return {};
// }
} // namespace noteTypeMapper
} // namespace ankicpp
