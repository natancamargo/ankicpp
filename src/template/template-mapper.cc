#include "note/note-type.h"
#include "template/template.h"
#include <memory>
namespace ankicpp {
namespace templateMapper {
TemplateDTO modelToDTO(Template &model) {
  TemplateDTO templateDTO;

  if (std::shared_ptr<NoteType> noteType = model.getNoteType().lock()) {
    templateDTO.ntid = noteType->getId();
    templateDTO.ord =
        noteType->getTemplateIndex(std::make_shared<Template>(model));
  }
  templateDTO.name = model.getName();
  templateDTO.mtime_secs = 0;
  templateDTO.usn = 0;

  if (model.getId() == basicTemplate->getId()) {
    templateDTO.config.insert(templateDTO.config.end(), {0x0a, 0x09});
  } else if (model.getId() == reversedTemplate->getId()) {
    templateDTO.config.insert(templateDTO.config.end(), {0x0a, 0x08});
  }
  const std::string &frontTemplte = model.getFrontTemplate();
  const std::string &backTemplte = model.getBackTemplate();
  std::copy(frontTemplte.begin(), frontTemplte.end(),
            std::back_inserter(templateDTO.config));
  if (model.getId() == basicTemplate->getId()) {
    templateDTO.config.insert(templateDTO.config.end(), {0x12, 0x27});
  } else if (model.getId() == reversedTemplate->getId()) {
    templateDTO.config.insert(templateDTO.config.end(), {0x12, 0x28});
  }
  std::copy(backTemplte.begin(), backTemplte.end(),
            std::back_inserter(templateDTO.config));
  templateDTO.config.insert(templateDTO.config.end(),
                            {0x40, 0xf4, 0xcf, 0xec, 0xe0, 0xf8, 0xdf, 0xf1,
                             0xce, 0x51}); // anki magic numbers
  return templateDTO;
}
// Template modelFromDTO(TemplateDTO dto) {
//   return {};
// }
} // namespace templateMapper
} // namespace ankicpp
