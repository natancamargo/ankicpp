#include "template/template.h"

namespace ankicpp {
  Template::Template(std::string name) : _name(name) {}

  std::string Template::getName() const { return _name; }
  void Template::setName(std::string name) { _name = name; }

  std::string Template::getFrontTemplate() const { return _frontTemplate; }
  void Template::setFrontTemplate(std::string frontTemplate) {
    _frontTemplate = frontTemplate;
  }

  std::string Template::getBackTemplate() const { return _backTemplate; }
  void Template::setBackTemplate(std::string backTemplate) {
    _backTemplate = backTemplate;
  }

  NoteType *Template::getNoteType() { return _noteType; }
  void Template::setNoteType(NoteType *noteType) { _noteType = noteType; }
} // namespace ankicpp
