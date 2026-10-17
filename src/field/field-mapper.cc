#include "deck/deck.h"
#include "field/field-dto.h"
#include "field/field.h"
#include "resources/proto/note-type.pb.h"
#include <memory>

namespace ankicpp {
namespace fieldMapper {
FieldDTO modelToDTO(Field &model) {
  FieldDTO fieldDTO;
  if (std::shared_ptr<NoteType> noteType = model.getNoteType().lock()) {
    fieldDTO.ntid = noteType->getId();
    fieldDTO.ord = noteType->getFieldIndex(std::make_shared<Field>(model));
  }

  fieldDTO.name = model.getName();

  anki::Notetype::Field::Config config;

  const std::string &font = model.getFont();
  config.set_font_name(font);

  const uint &fontSize = model.getFontSize();
  config.set_font_size(fontSize);

  config.set_id(fieldDTO.ntid);
  std::string configSerialized = config.SerializeAsString();
  std::copy(configSerialized.begin(), configSerialized.end(),
            std::back_inserter(fieldDTO.config));

  return fieldDTO;
}
// Field modelFromDTO(FieldDTO dto) {
//   return {};
// }
} // namespace fieldMapper
} // namespace ankicpp
