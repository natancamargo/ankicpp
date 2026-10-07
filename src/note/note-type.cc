#include "note/note-type.h"
#include "template/template.h"
#include "util/nameable.h"
#include <algorithm>
#include <cstddef>
#include <memory>
#include <string>

namespace ankicpp {
NoteType::NoteType(std::string name) : Nameable(name) {}

std::vector<std::shared_ptr<Template>> &NoteType::getTemplates() {
  return _templates;
}
void NoteType::addTemplate(std::shared_ptr<Template> templatee) {
  auto it = std::find(_templates.begin(), _templates.end(), templatee);
  if (it == _templates.end()) {
    _templates.push_back(templatee);
  }
}
std::size_t NoteType::getTemplateIndex(std::shared_ptr<Template> templatee) {
  auto it = std::find_if(_templates.begin(), _templates.end(),
                         [templatee](std::shared_ptr<Template> _templatee) {
                           return *templatee == *_templatee;
                         });
  std::size_t index = std::distance(_templates.begin(), it);
  if (index < _templates.size()) {
    return index;
  }
  return 0;
}

void NoteType::removeTemplate(std::shared_ptr<Template> templatee) {
  _templates.erase(
      std::remove(_templates.begin(), _templates.end(), templatee));
}

std::vector<std::shared_ptr<Field>> &NoteType::getFields() { return _fields; }
void NoteType::addField(std::shared_ptr<Field> field) {
  auto it = std::find(_fields.begin(), _fields.end(), field);
  if (it == _fields.end()) {
    _fields.push_back(field);
  }
}
std::size_t NoteType::getFieldIndex(std::shared_ptr<Field> field) {
  auto it = std::find_if(
      _fields.begin(), _fields.end(),
      [field](std::shared_ptr<Field> _field) { return *field == *_field; });
  std::size_t index = std::distance(_fields.begin(), it);
  if (index < _fields.size()) {
    return index;
  }
  return 0;
}
void NoteType::removeField(std::shared_ptr<Field> field) {
  _fields.erase(std::remove(_fields.begin(), _fields.end(), field));
}

std::string NoteType::getHeader() const { return _header; }
void NoteType::setHeader(std::string header) { _header = header; }

std::string NoteType::getFooter() const { return _footer; }
void NoteType::setFooter(std::string footer) { _footer = footer; }

std::string NoteType::getStyle() const { return _style; }
void NoteType::setStyle(std::string style) { _style = style; }

const std::shared_ptr<Template> basicTemplate = []() {
  const std::shared_ptr<Template> templatee =
      std::make_shared<Template>("ankicpp::Basic::Card1");
  templatee->setFrontTemplate("{{Front}}");
  templatee->setBackTemplate("{{FrontSide}}\n\n<hr id=answer>\n\n{{Back}}");
  return templatee;
}();

const std::shared_ptr<NoteType> basicNoteType = []() {
  const std::shared_ptr<NoteType> noteType =
      std::make_shared<NoteType>("ankicpp::Basic");
  basicTemplate->setNoteType(noteType);
  noteType->addTemplate(basicTemplate);
  noteType->setStyle(R"(.card {
    font-family: arial;
    font-size: 20px;
    line-height: 1.5;
    text-align: center;
    color: black;
    background-color: white;
})");
  noteType->setHeader(R"(\documentclass[12pt]{article}
\special{papersize=3in,5in}
\usepackage[utf8]{inputenc}
\usepackage{amssymb,amsmath}
\pagestyle{empty}
\setlength{\parindent}{0in}
\begin{document})");
  noteType->setFooter("\\end{document}");
  std::shared_ptr<Field> frontField = std::make_shared<Field>("Front");
  frontField->setFont("Arial");
  frontField->setFontSize(20);
  frontField->setNoteType(noteType);  
  noteType->addField(frontField);  
  std::shared_ptr<Field> backField = std::make_shared<Field>("Back");
  backField->setFont("Arial");
  backField->setFontSize(20);
  backField->setNoteType(noteType);  
  noteType->addField(backField);
  return noteType;
}();

const std::shared_ptr<Template> clozeTemplate = []() {
  const std::shared_ptr<Template> templatee =
      std::make_shared<Template>("ankicpp::Basic::Card1");
  templatee->setFrontTemplate("{{cloze:Text}}");
  templatee->setBackTemplate(R"({{cloze:Text}}<br>
{{Back Extra}})");
  return templatee;
}();

const std::shared_ptr<NoteType> clozeNoteType = []() {
  const std::shared_ptr<NoteType> noteType =
      std::make_shared<NoteType>("ankicpp::Basic");
  noteType->addTemplate(basicTemplate);
  basicTemplate->setNoteType(noteType);
  noteType->setStyle(R"(.card {
    font-family: arial;
    font-size: 20px;
    line-height: 1.5;
    text-align: center;
    color: black;
    background-color: white;
}
.cloze {
    font-weight: bold;
    color: blue;
}
.nightMode .cloze {
    color: lightblue;
}
)");
  noteType->setHeader(R"(\documentclass[12pt]{article}
\special{papersize=3in,5in}
\usepackage[utf8]{inputenc}
\usepackage{amssymb,amsmath}
\pagestyle{empty}
\setlength{\parindent}{0in}
\begin{document}
)");
  noteType->setFooter("\\end{document}");
  std::shared_ptr<Field> textField = std::make_shared<Field>("Text");
  textField->setFont("Arial");
  textField->setFontSize(20);
  textField->setNoteType(noteType);
  noteType->addField(textField);
  std::shared_ptr<Field> backField = std::make_shared<Field>("Back Extra");
  backField->setFont("Arial");
  backField->setFontSize(20);
  backField->setNoteType(noteType);
  noteType->addField(backField);
  return noteType;
}();
} // namespace ankicpp
