#include "note/note-type.h"

namespace ankicpp {
  NoteType::NoteType(std::string name) : _name(name) {}

  std::int64_t NoteType::getId() {
    return _id;
  }
  void NoteType::setId(std::int64_t id) {
    _id = id;
  }

  std::string NoteType::getName() {
    return _name;
  }
  void NoteType::setName(std::string name) {
    _name = name;
  }
 
  std::list<Field> &NoteType::getFields() {
    return _fields;
  }
  void NoteType::addField(std::string name) {
    auto it = std::find_if(_fields.begin(), _fields.end(), [name](Field field){
      return field.getName() == name;
    });
    if (it == _fields.end()) {
      _fields.push_back({ name });
    }
  }
  void NoteType::removeField(std::string name) {
    _fields.remove_if([name](Field field){ return field.getName() == name; });
  }

  std::string NoteType::getHeader() {
    return _header;
  }
  void NoteType::setHeader(std::string header) {
    _header = header;
  }

  std::string NoteType::getFooter() {
    return _footer;
  }
  void NoteType::setFooter(std::string footer) {
    _footer = footer;
  }

  std::string NoteType::getStyle() {
    return _style;
  }
  void NoteType::setStyle(std::string style) {
    _style = style;
  }
}
