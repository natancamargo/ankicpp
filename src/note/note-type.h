#pragma once

#include <memory>
#include <string>

#include "field/field.h"
#include "template/template.h"
#include "util/identifyable.h"
#include "util/nameable.h"

namespace ankicpp {
class NoteType : public Identifyable,
                 public Nameable,
                 public std::enable_shared_from_this<NoteType> {
public:
  NoteType(std::string name);

  std::vector<std::shared_ptr<Template>> &getTemplates();
  void addTemplate(std::shared_ptr<Template> templatee);
  void removeTemplate(std::shared_ptr<Template> templatee);
  std::size_t getTemplateIndex(std::shared_ptr<Template> templatee);

  std::vector<std::shared_ptr<Field>> &getFields();
  void addField(std::shared_ptr<Field> field);
  void removeField(std::shared_ptr<Field> field);
  std::size_t getFieldIndex(std::shared_ptr<Field> field);

  std::string getHeader() const;
  void setHeader(std::string header);

  std::string getFooter() const;
  void setFooter(std::string footer);

  std::string getStyle() const;
  void setStyle(std::string style);

private:
  std::vector<std::shared_ptr<Template>> _templates;
  std::vector<std::shared_ptr<Field>> _fields;
  std::string _header;
  std::string _footer;
  std::string _style;
};

extern const std::shared_ptr<Template> basicTemplate;
extern const std::shared_ptr<Template> reversedTemplate;
extern const std::shared_ptr<NoteType> basicNoteType;
extern const std::shared_ptr<NoteType> basicAndReversedNoteType;

extern const std::shared_ptr<Template> clozeTemplate;
extern const std::shared_ptr<NoteType> clozeNoteType;
} // namespace ankicpp
