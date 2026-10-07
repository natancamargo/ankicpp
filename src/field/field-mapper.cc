#include "deck/deck.h"
#include "field/field-dto.h"
#include "field/field.h"
#include <memory>
namespace ankicpp {
namespace fieldMapper {
FieldDTO modelToDTO(Field &model) {
  FieldDTO fieldDTO;
  fieldDTO.ntid = model.getNoteType()->getId();
  fieldDTO.ord =
      model.getNoteType()->getFieldIndex(std::make_shared<Field>(model));
  fieldDTO.name = model.getName();

  fieldDTO.config.insert(fieldDTO.config.end(), {0x1a, 0x05}); // SUB HTAENQ
  const std::string &font = model.getFont();
  //  const std::string &fontSize = model.getFontSize();
  std::copy(font.begin(), font.end(), std::back_inserter(fieldDTO.config));
  //  TODO: Font size may be the 0x14 below.  
  fieldDTO.config.insert(fieldDTO.config.end(),
                         {0x20, 0x14, 0x48, 0x82, 0xca, 0xd7, 0x95, 0xc2, 0xe3,
                          0x81, 0xdb, 0x77});

  return fieldDTO;
}
// Field modelFromDTO(FieldDTO dto) {
//   return {};
// }
} // namespace fieldMapper
} // namespace ankicpp
