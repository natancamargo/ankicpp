#include "deck/deck.h"
#include "note/note-type-dto.h"
#include "note/note-type.h"
namespace ankicpp {
namespace noteTypeMapper {
NoteTypeDTO modelToDTO(NoteType &model) {
  NoteTypeDTO noteTypeDTO;
  noteTypeDTO.id = model.getId();
  noteTypeDTO.name = model.getName();
  noteTypeDTO.mtime_secs = 0;
  noteTypeDTO.usn = 0;

  noteTypeDTO.config.insert(noteTypeDTO.config.end(), {0x1a, 0x94, 0x01});
  const std::string &header = model.getHeader();
  const std::string &footer = model.getFooter();
  const std::string &style = model.getStyle();
  std::copy(style.begin(), style.end(), std::back_inserter(noteTypeDTO.config));

  noteTypeDTO.config.insert(noteTypeDTO.config.end(), {0x0a, 0x2a, 0xb2, 0x01});
  std::copy(header.begin(), header.end(),
            std::back_inserter(noteTypeDTO.config));
  noteTypeDTO.config.insert(noteTypeDTO.config.end(), {0x0a, 0x32, 0x0e});
  std::copy(footer.begin(), footer.end(),
            std::back_inserter(noteTypeDTO.config));
  noteTypeDTO.config.insert(
      noteTypeDTO.config.end(),
      {0x42, 0x05, 0x10, 0x01, 0x1a, 0x01, 0x00, 0x48, 0x01});

      return noteTypeDTO;
}
// NoteType modelFromDTO(NoteTypeDTO dto) {
//   return {};
// }
} // namespace noteTypeMapper
} // namespace ankicpp
