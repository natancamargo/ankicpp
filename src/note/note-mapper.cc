#include "note/note-dto.h"
#include "note/note.h"
#include "util/identifyable.h"
#include <string>
#include <tuple>
#include <uuid/uuid.h>
namespace ankicpp {
namespace noteMapper {
NoteDTO modelToDTO(Note &model) {
  NoteDTO noteDTO;
  noteDTO.id = model.getId();
  noteDTO.guid = std::to_string(Identifyable::generateRandomId());
  noteDTO.mid = model.getType()->getId();
  noteDTO.mod = 0;
  noteDTO.usn = 0;
  noteDTO.csum = 0;
  noteDTO.data = "";
  noteDTO.flags = 0;

  for (std::set<std::string>::iterator it = model.getTags().begin();
       it != model.getTags().end(); ++it) {
    std::string tag = *it;
    noteDTO.tags += tag;
    std::size_t index = std::distance(model.getTags().begin(), it);
    if (index < model.getTags().size() - 1) {
      noteDTO.tags.push_back(0x1F);
    }
  }

  for (std::vector<std::tuple<std::string, std::string>>::const_iterator it =
           model.getFields().begin();
       it != model.getFields().end(); ++it) {
    std::string field = std::get<1>(*it);
    noteDTO.flds += field;
    std::size_t index = std::distance(model.getFields().begin(), it);
    if (index < model.getFields().size() - 1) {
      noteDTO.flds.push_back(0x1F);
    }
    if (index == 0) {
      noteDTO.sfld = field;
    }
  }

  return noteDTO;
}
// Note modelFromDTO(NoteDTO dto) {
//   return {};
// }
} // namespace noteMapper
} // namespace ankicpp
