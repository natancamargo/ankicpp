#include "note/note.h"

namespace ankicpp {
  std::int64_t Note::getId() const {
    return _id;
  }
  void Note::setId(std::int64_t id) {
    _id = id;
  }

  NoteType *Note::getType() const {
    return _type;
  }
  void Note::setType(NoteType* type) {
    _type = type;
  }

  std::map<std::string, std::string> &Note::getFields() {
    return _fields;
  }
  std::string Note::getField(std::string name) {
    return _fields[name];
  }
  void Note::setField(std::string name, std::string value) {
    _fields[name] = value;
  }
 
  std::set<std::string> &Note::getTags() {
    return _tags;
  }
  void Note::addTag(std::string name) {
    _tags.insert(name);
  }
  void Note::removeTag(std::string name) {
    _tags.erase(name);
  }

  int Note::getFlags() const {
    return _flags;
  }
  void Note::setFlags(int flags) {
    _flags = flags;
  }
}
