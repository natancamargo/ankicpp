#pragma once

#include <set>
#include <string>

#include "note/note-type.h"
#include "util/identifyable.h"

namespace ankicpp {
class Note : public Identifyable {
public:
  std::shared_ptr<NoteType> getType() const;
  void setType(std::shared_ptr<NoteType> noteType);

  std::vector<std::tuple<std::string, std::string>> &getFields();
  std::string getField(std::string name);
  void addField(std::string name, std::string value);
  void removeField(std::string name);

  std::set<std::string> &getTags();
  void addTag(std::string name);
  void removeTag(std::string name);

  int getFlags() const;
  void setFlags(int flags);

private:
  std::shared_ptr<NoteType> _noteType;
  std::vector<std::tuple<std::string, std::string>> _fields;
  std::set<std::string> _tags;
  int _flags = 0;
};
} // namespace ankicpp
