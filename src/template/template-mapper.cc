#include "note/note-type.h"
#include "template/template.h"
#include <memory>
namespace ankicpp {
  namespace templateMapper {
    TemplateDTO modelToDTO(Template &model) {
      TemplateDTO templateDTO;

      templateDTO.ntid = model.getNoteType()->getId();
      templateDTO.ord =
        model.getNoteType()->getTemplateIndex(std::make_shared<Template>(model));
      templateDTO.name = model.getName();
      templateDTO.mtime_secs = 0;
      templateDTO.usn = 0;

      templateDTO.config.insert(templateDTO.config.end(), {0x0a, 0x09}); // LF HTAB
      const std::string &frontTemplte = model.getFrontTemplate();
      const std::string &backTemplte = model.getBackTemplate();
      std::copy(frontTemplte.begin(), frontTemplte.end(),
                std::back_inserter(templateDTO.config));
      templateDTO.config.insert(templateDTO.config.end(),
                                {0x12, 0x27}); // LF two times
      std::copy(backTemplte.begin(), backTemplte.end(),
                std::back_inserter(templateDTO.config));
      templateDTO.config.insert(templateDTO.config.end(),
                                {0x40, 0xf4, 0xcf, 0xec, 0xe0, 0xf8, 0xdf, 0xf1, 0xce, 0x51}); // anki magic numbers
      return templateDTO;
    }
    // Template modelFromDTO(TemplateDTO dto) {
    //   return {};
    // }
  } // namespace templateMapper
} // namespace ankicpp
