#pragma once

#include <list>
#include <string>
#include <algorithm>

#include "field/field.h"
#include "util/time.h"

namespace ankicpp {
  class NoteType {
  public:
    NoteType() = default;
    NoteType(std::string name);

    std::int64_t getId();
    void setId(std::int64_t id);

    std::string getName();
    void setName(std::string name);

    std::list<Field> &getFields();
    void addField(std::string name);
    void removeField(std::string name);

    std::string getHeader();
    void setHeader(std::string header);

    std::string getFooter();
    void setFooter(std::string footer);

    std::string getStyle();
    void setStyle(std::string style);
  private:
    std::int64_t _id = getNow();
    std::string _name;
    std::list<Field> _fields;
    std::string _header;
    std::string _footer;
    std::string _style;
  };
}
