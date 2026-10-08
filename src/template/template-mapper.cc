#include "note/note-type.h"
#include "template/template.h"
#include <memory>
namespace ankicpp {
namespace templateMapper {
TemplateDTO modelToDTO(Template &model) {
  TemplateDTO templateDTO;

  templateDTO.ntid = model.getNoteType().lock()->getId();
  templateDTO.ord = model.getNoteType().lock()->getTemplateIndex(
      std::make_shared<Template>(model));
  templateDTO.name = model.getName();
  templateDTO.mtime_secs = 0;
  templateDTO.usn = 0;

  const std::string &frontTemplte = model.getFrontTemplate();
  const std::string &backTemplte = model.getBackTemplate();
  std::copy(frontTemplte.begin(), frontTemplte.end(),
            std::back_inserter(templateDTO.config));
  std::copy(backTemplte.begin(), backTemplte.end(),
            std::back_inserter(templateDTO.config));
  return templateDTO;
}
// Template modelFromDTO(TemplateDTO dto) {
//   return {};
// }
} // namespace templateMapper
} // namespace ankicpp
