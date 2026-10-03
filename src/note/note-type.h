#pragma once

#include <cstdint>
#include <list>
#include <memory>
#include <string>

#include "template/template.h"
#include "field/field.h"
#include "util/time.h"

namespace ankicpp {
class NoteType {
public:
  NoteType(std::string name);

  std::int64_t getId() const;
  void setId(std::int64_t id);

  std::string getName() const;
  void setName(std::string name);

  std::list<Template *> &getTemplates();
  void addTemplate(Template *cardType);
  void removeTemplate(Template *cardType);

  std::list<Field *> &getFields();
  void addField(Field *field);
  void removeField(Field *field);

  std::string getHeader() const;
  void setHeader(std::string header);

  std::string getFooter() const;
  void setFooter(std::string footer);

  std::string getStyle() const;
  void setStyle(std::string style);

private:
  std::int64_t _id = getNow();
  std::string _name;
  std::list<Template *> _templates;
  std::list<Field *> _fields;
  std::string _header;
  std::string _footer;
  std::string _style;
};

extern std::shared_ptr<NoteType> BasicNoteTypeSmartPtr;
extern std::shared_ptr<NoteType> ClozeNoteTypeSmartPtr;
extern NoteType *BasicNoteType;
extern NoteType *ClozeNoteType;
} // namespace ankicpp
