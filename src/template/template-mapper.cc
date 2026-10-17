#include "note/note-type.h"
#include "template/template.h"
#include "resources/proto/note-type.pb.h"

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

  anki::Notetype::Template::Config config;

  const std::string &frontTemplate = model.getFrontTemplate();  
  config.set_q_format(frontTemplate);

  const std::string &backTemplate = model.getFrontTemplate();  
  config.set_a_format(backTemplate);

  config.set_id(templateDTO.ntid);

  std::string configSerialized = config.SerializeAsString();
  std::copy(configSerialized.begin(), configSerialized.end(),
            std::back_inserter(templateDTO.config));

  return templateDTO;
}
// Template modelFromDTO(TemplateDTO dto) {
//   return {};
// }
} // namespace templateMapper
} // namespace ankicpp
