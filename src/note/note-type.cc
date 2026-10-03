#include "note/note-type.h"
#include <algorithm>

namespace ankicpp {
NoteType::NoteType(std::string name) : _name(name) {}

std::int64_t NoteType::getId() const { return _id; }
void NoteType::setId(std::int64_t id) { _id = id; }

std::string NoteType::getName() const { return _name; }
void NoteType::setName(std::string name) { _name = name; }

std::list<Template *> &NoteType::getTemplates() { return _templates; }
void NoteType::addTemplate(Template *templatee) {
  auto it = std::find_if(
      _templates.begin(), _templates.end(),
      [templatee](Template *_cardType) { return templatee == _cardType; });
  if (it == _templates.end()) {
    _templates.push_back(templatee);
  }
}
void NoteType::removeTemplate(Template *cardType) {
  _templates.remove(cardType);
}

std::list<Field *> &NoteType::getFields() { return _fields; }
void NoteType::addField(Field *field) {
  auto it = std::find_if(_fields.begin(), _fields.end(),
                         [field](Field *_field) { return field == _field; });
  if (it == _fields.end()) {
    _fields.push_back(field);
  }
}
void NoteType::removeField(Field *field) { _fields.remove(field); }

std::string NoteType::getHeader() const { return _header; }
void NoteType::setHeader(std::string header) { _header = header; }

std::string NoteType::getFooter() const { return _footer; }
void NoteType::setFooter(std::string footer) { _footer = footer; }

std::string NoteType::getStyle() const { return _style; }
void NoteType::setStyle(std::string style) { _style = style; }

std::shared_ptr<NoteType> BasicNoteTypeSmartPtr =
    std::make_shared<NoteType>("ankicpp::Basic");
std::shared_ptr<NoteType> ClozeNoteTypeSmartPtr =
    std::make_shared<NoteType>("ankicpp::Cloze");
NoteType *BasicNoteType = BasicNoteTypeSmartPtr.get();
NoteType *ClozeNoteType = ClozeNoteTypeSmartPtr.get();
} // namespace ankicpp
