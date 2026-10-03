#include "note/note.h"
#include "util/time.h"

namespace ankicpp {
Note::Note() {
  static std::uint32_t ids = 0;  
  _id = ids++;  
}

std::shared_ptr<NoteType> Note::getType() const { return _noteType; }
void Note::setType(std::shared_ptr<NoteType> noteType) { _noteType = noteType; }

std::map<std::string, std::string> &Note::getFields() { return _fields; }
std::string Note::getField(std::string name) { return _fields[name]; }
void Note::addField(std::string name, std::string value) {
  _fields[name] = value;
}
void Note::removeField(std::string name) { _fields.erase(name); }

std::set<std::string> &Note::getTags() { return _tags; }
void Note::addTag(std::string name) { _tags.insert(name); }
void Note::removeTag(std::string name) { _tags.erase(name); }

int Note::getFlags() const { return _flags; }
void Note::setFlags(int flags) { _flags = flags; }
} // namespace ankicpp
