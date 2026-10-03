#include "template/template.h"
#include "util/nameable.h"

namespace ankicpp {
Template::Template(std::string name) : Nameable(name) {}

std::string Template::getFrontTemplate() const { return _frontTemplate; }
void Template::setFrontTemplate(std::string frontTemplate) {
  _frontTemplate = frontTemplate;
}

std::string Template::getBackTemplate() const { return _backTemplate; }
void Template::setBackTemplate(std::string backTemplate) {
  _backTemplate = backTemplate;
}

std::shared_ptr<NoteType> Template::getNoteType() { return _noteType; }
void Template::setNoteType(std::shared_ptr<NoteType> noteType) {
  _noteType = noteType;
}
} // namespace ankicpp
