#include "note/note.h"
#include <algorithm>
#include <string>
#include <tuple>

namespace ankicpp {
const std::shared_ptr<NoteType> &Note::getType() const { return _noteType; }
void Note::setType(const std::shared_ptr<NoteType> &noteType) {
  _noteType = noteType;
}

const std::vector<std::tuple<std::string, std::string>> &
Note::getFields() const {
  return _fields;
}
void Note::setFields(
    const std::vector<std::tuple<std::string, std::string>> &fields) {
  _fields = fields;
}
std::string Note::getField(std::string name) {
  auto it = std::find_if(_fields.begin(), _fields.end(),
                         [name](const std::tuple<std::string, std::string> &e) {
                           return std::get<0>(e) == name;
                         });
  if (it != _fields.end()) {
    return std::get<1>(*it);
  }
  return "";
}
void Note::addField(std::string name, std::string value) {
  auto it = std::find_if(_fields.begin(), _fields.end(),
                         [name](const std::tuple<std::string, std::string> &e) {
                           return std::get<0>(e) == name;
                         });
  if (it != _fields.end()) {
    std::get<1>(*it) = value;
  } else {
    _fields.push_back(std::make_tuple(name, value));
  }
}
void Note::removeField(std::string name) {
  auto it = std::find_if(_fields.begin(), _fields.end(),
                         [name](const std::tuple<std::string, std::string> &e) {
                           return std::get<0>(e) == name;
                         });
  if (it != _fields.end()) {
    _fields.erase(it);
  }
}

const std::set<std::string> &Note::getTags() const { return _tags; }
void Note::setTags(const std::set<std::string> &tags) { _tags = tags; }
void Note::addTag(std::string name) { _tags.insert(name); }
void Note::removeTag(std::string name) { _tags.erase(name); }

int Note::getFlags() const { return _flags; }
void Note::setFlags(int flags) { _flags = flags; }

const std::shared_ptr<Note> &Note::getReversedParent() { return _reversedParent; }
void Note::setReversedParent(const std::shared_ptr<Note> &reversedParent) {
  _reversedParent = reversedParent;
}

} // namespace ankicpp
