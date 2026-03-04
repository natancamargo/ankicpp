#pragma once

#include <string>
#include <map>
#include <set>

#include "util/time.h"
#include "note/note-type.h"

namespace ankicpp {
  class Note {
  public:
    std::int64_t getId();
    void setId(std::int64_t id);

    NoteType *getType();
    void setType(NoteType *type);

    const std::map<std::string, std::string> &getFields();
    std::string getField(std::string name);
    void setField(std::string name, std::string value);
 
    std::set<std::string> &getTags();
    void addTag(std::string name);
    void removeTag(std::string name);

    int getFlags();
    void setFlags(int flags);
  private:
    std::int64_t _id = getNow();
    NoteType *_type;
    std::map<std::string, std::string> _fields;
    std::set<std::string> _tags;
    int _flags;
  };
}
