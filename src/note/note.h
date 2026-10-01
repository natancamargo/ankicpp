#pragma once

#include <cstdint>
#include <map>
#include <set>
#include <string>

#include "note/note-dto.h"
#include "note/note-type-dto.h"
#include "note/note-type.h"
#include "util/time.h"

namespace ankicpp {
class Note {
public:
  std::int64_t getId() const;
  void setId(std::int64_t id);

  NoteType *getType() const;
  void setType(NoteType *type);

  std::map<std::string, std::string> &getFields();
  std::string getField(std::string name);
  void addField(std::string name, std::string value);
  void removeField(std::string name);

  std::set<std::string> &getTags();
  void addTag(std::string name);
  void removeTag(std::string name);

  int getFlags() const;
  void setFlags(int flags);

  bool operator==(const Note &rhs);
  bool operator!=(const Note &rhs);
  bool operator<(const Note &rhs);

private:
  std::int64_t _id = getNow();
  NoteType *_type;
  std::map<std::string, std::string> _fields;
  std::set<std::string> _tags;
  int _flags = 0;
};
} // namespace ankicpp
