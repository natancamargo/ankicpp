#pragma once

#include <string>
#include <map>
#include <set>
#include <cstdint>

#include "util/time.h"
#include "note/note-type.h"

namespace ankicpp {
  class Note {
  public:
    std::int64_t getId() const;
    void setId(std::int64_t id);

    NoteType *getType() const;
    void setType(NoteType *type);

    std::map<std::string, std::string> &getFields();
    std::string getField(std::string name);
    void setField(std::string name, std::string value);
 
    std::set<std::string> &getTags();
    void addTag(std::string name);
    void removeTag(std::string name);

    int getFlags() const;
    void setFlags(int flags);
  private:
    std::int64_t _id = getNow();
    NoteType *_type;
    std::map<std::string, std::string> _fields;
    std::set<std::string> _tags;
    int _flags;
  };
}
