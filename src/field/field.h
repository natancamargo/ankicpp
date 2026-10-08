#pragma once

#include "field/field-dto.h"
#include "util/identifyable.h"
#include "util/nameable.h"
#include <memory>
#include <string>

namespace ankicpp {
class NoteType;
class Field : public Identifyable, public Nameable {
public:
  Field(std::string name);

  std::weak_ptr<NoteType> getNoteType() const;
  void setNoteType(std::weak_ptr<NoteType> noteType);

  std::string getDescription() const;
  void setDescription(std::string description);

  std::string getFont() const;
  void setFont(std::string font);

  uint getFontSize() const;
  void setFontSize(uint fontSize);

private:
  std::weak_ptr<NoteType> _noteType;
  std::string _description;
  std::string _font;
  uint _fontSize;
};
} // namespace ankicpp
