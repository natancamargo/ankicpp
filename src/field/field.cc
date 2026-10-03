#include "field/field.h"
#include "util/nameable.h"

namespace ankicpp {
Field::Field(std::string name) : Nameable(name) {
  static std::uint32_t ids = 0;
  _id = ids++;
}

std::shared_ptr<NoteType> Field::getNoteType() const { return _noteType; }
void Field::setNoteType(std::shared_ptr<NoteType> noteType) {
  _noteType = noteType;
}

std::string Field::getDescription() const { return _description; }
void Field::setDescription(std::string description) {
  _description = description;
}

std::string Field::getFont() const { return _font; }
void Field::setFont(std::string font) { _font = font; }

uint Field::getFontSize() const { return _fontSize; }
void Field::setFontSize(uint fontSize) { _fontSize = fontSize; }

} // namespace ankicpp
