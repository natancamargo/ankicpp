#include "note/note-type.h"
#include "util/nameable.h"
#include <algorithm>
#include <cstddef>
#include <memory>
#include <string>

namespace ankicpp {
NoteType::NoteType(std::string name) : Nameable(name) {
  static std::uint32_t ids = 0;
  _id = ids++;
}

std::vector<std::shared_ptr<Template>> &NoteType::getTemplates() {
  return _templates;
}
void NoteType::addTemplate(std::shared_ptr<Template> templatee) {
  auto it = std::find(_templates.begin(), _templates.end(), templatee);
  if (it == _templates.end()) {
    _templates.push_back(templatee);
    templatee->setNoteType(std::make_shared<NoteType>(*this));
  }
}
std::size_t NoteType::getTemplateIndex(std::shared_ptr<Template> templatee) {
  auto it = std::find(_templates.begin(), _templates.end(), templatee);
  std::size_t index = (it - _templates.begin());
  if (index < _templates.size()) {
    return index;
  }
  return -1;  
}

void NoteType::removeTemplate(std::shared_ptr<Template> templatee) {
  _templates.erase(
      std::remove(_templates.begin(), _templates.end(), templatee));
  templatee->setNoteType(nullptr);
}

std::vector<std::shared_ptr<Field>> &NoteType::getFields() { return _fields; }
void NoteType::addField(std::shared_ptr<Field> field) {
  auto it = std::find(_fields.begin(), _fields.end(), field);
  if (it == _fields.end()) {
    _fields.push_back(field);
    field->setNoteType(std::make_shared<NoteType>(*this));
  }
}
void NoteType::removeField(std::shared_ptr<Field> field) {
  _fields.erase(std::remove(_fields.begin(), _fields.end(), field));
  field->setNoteType(nullptr);
}

std::string NoteType::getHeader() const { return _header; }
void NoteType::setHeader(std::string header) { _header = header; }

std::string NoteType::getFooter() const { return _footer; }
void NoteType::setFooter(std::string footer) { _footer = footer; }

std::string NoteType::getStyle() const { return _style; }
void NoteType::setStyle(std::string style) { _style = style; }

std::shared_ptr<Template> basicTemplate = []() {
  const std::shared_ptr<Template> templatee =
      std::make_shared<Template>("ankicpp::Basic::Card1");
  templatee->setFrontTemplate("{{Front}}");
  templatee->setBackTemplate(R"(
{{FrontSide}}
  <hr id=answer>
{{Back}}
)");
  return templatee;
}();

std::shared_ptr<NoteType> basicNoteType = []() {
  const std::shared_ptr<NoteType> noteType =
      std::make_shared<NoteType>("ankicpp::Basic");
  noteType->addTemplate(basicTemplate);
  noteType->setStyle(R"(
.card {
    font-family: arial;
    font-size: 20px;
    line-height: 1.5;
    text-align: center;
    color: black;
    background-color: white;
}
)");
  noteType->setHeader(R"(
\documentclass[12pt]{article}
\special{papersize=3in,5in}
\usepackage[utf8]{inputenc}
\usepackage{amssymb,amsmath}
\pagestyle{empty}
\setlength{\parindent}{0in}
\begin{document}
)");
  noteType->setFooter("\end{document}");
  std::shared_ptr<Field> frontField = std::make_shared<Field>("Front");
  frontField->setFont("Arimo");
  frontField->setFontSize(20);
  noteType->addField(frontField);
  std::shared_ptr<Field> backField = std::make_shared<Field>("Back");
  backField->setFont("Arimo");
  backField->setFontSize(20);
  noteType->addField(backField);
  return noteType;
}();

std::shared_ptr<Template> clozeTemplate = []() {
  const std::shared_ptr<Template> templatee =
      std::make_shared<Template>("ankicpp::Basic::Card1");
  templatee->setFrontTemplate("{{cloze:Text}}");
  templatee->setBackTemplate(R"(
{{cloze:Text}}<br>
{{Back Extra}}
)");
  return templatee;
}();

std::shared_ptr<NoteType> clozeNoteType = []() {
  const std::shared_ptr<NoteType> noteType =
      std::make_shared<NoteType>("ankicpp::Basic");
  noteType->addTemplate(basicTemplate);
  noteType->setStyle(R"(
.card {
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
  noteType->setHeader(R"(
\documentclass[12pt]{article}
\special{papersize=3in,5in}
\usepackage[utf8]{inputenc}
\usepackage{amssymb,amsmath}
\pagestyle{empty}
\setlength{\parindent}{0in}
\begin{document}
)");
  noteType->setFooter("\end{document}");
  std::shared_ptr<Field> textField = std::make_shared<Field>("Text");
  textField->setFont("Arimo");
  textField->setFontSize(20);
  noteType->addField(textField);
  std::shared_ptr<Field> backField = std::make_shared<Field>("Back Extra");
  backField->setFont("Arimo");
  backField->setFontSize(20);
  noteType->addField(backField);
  return noteType;
}();
} // namespace ankicpp
