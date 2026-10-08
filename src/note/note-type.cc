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
void NoteType::addTemplate(std::shared_ptr<Template> templatee) {
  auto it = std::find_if(_templates.begin(), _templates.end(),
                         [templatee](std::shared_ptr<Template> _template) {
                           return *templatee == *_template;
                         });
  if (it == _templates.end()) {
    Template templateeCopy{*templatee};
    templateeCopy.setNoteType(shared_from_this());
    std::shared_ptr<Template> templatePtr =
        std::make_shared<Template>(std::move(templateeCopy));
    _templates.push_back(templatePtr);
  }
}
void NoteType::removeTemplate(std::shared_ptr<Template> templatee) {
  _templates.erase(
      std::remove(_templates.begin(), _templates.end(), templatee));
}

std::vector<std::shared_ptr<Field>> &NoteType::getFields() { return _fields; }
void NoteType::addField(std::shared_ptr<Field> field) {
  auto it = std::find_if(
      _fields.begin(), _fields.end(),
      [field](std::shared_ptr<Field> _field) { return *field == *_field; });
  if (it == _fields.end()) {
    Field fieldCopy{*field};
    fieldCopy.setNoteType(shared_from_this());
    std::shared_ptr<Field> fieldPtr =
        std::make_shared<Field>(std::move(fieldCopy));
    _fields.push_back(fieldPtr);
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

const std::string style = R"(.card {
    font-family: arial;
    font-size: 20px;
    line-height: 1.5;
    text-align: center;
    color: black;
    background-color: white;
})";

const std::string header = R"(\documentclass[12pt]{article}
\special{papersize=3in,5in}
\usepackage[utf8]{inputenc}
\usepackage{amssymb,amsmath}
\pagestyle{empty}
\setlength{\parindent}{0in}
\begin{document})";

const std::string footer = "\\end{document}";

const std::shared_ptr<Template> basicTemplate = []() {
  const std::shared_ptr<Template> templatee =
      std::make_shared<Template>("ankicpp::Basic::Card_1");
  templatee->setFrontTemplate("\x0a\x09{{Front}}");
  templatee->setBackTemplate("\x12\x27{{FrontSide}}\n\n<hr id=answer>\n\n{{Back}}\x40\xf4\xcf\xec\xe0\xf8\xdf\xf1\xce\x51");
  return templatee;
}();

const std::shared_ptr<Template> reversedTemplate = []() {
  const std::shared_ptr<Template> templatee =
      std::make_shared<Template>("ankicpp::Basic::Card_2");
  templatee->setFrontTemplate("\x0a\x08{{Back}}");
  templatee->setBackTemplate("\x12\x28{{FrontSide}}\n\n<hr id=answer>\n\n{{Front}}\x40\xf4\xcf\xec\xe0\xf8\xdf\xf1\xce\x51");
  return templatee;
}();

const std::shared_ptr<NoteType> basicNoteType = []() {
  const std::shared_ptr<NoteType> noteType =
      std::make_shared<NoteType>("ankicpp::Basic");
  noteType->addTemplate(basicTemplate);
  noteType->setStyle(style);
  noteType->setHeader(header);
  noteType->setFooter(footer);
  std::shared_ptr<Field> frontField = std::make_shared<Field>("Front");
  frontField->setFont("Arial");
  frontField->setFontSize(20);
  noteType->addField(frontField);
  std::shared_ptr<Field> backField = std::make_shared<Field>("Back");
  backField->setFont("Arial");
  backField->setFontSize(20);
  noteType->addField(backField);
  return noteType;
}();

const std::shared_ptr<NoteType> basicAndReversedNoteType = []() {
  const std::shared_ptr<NoteType> noteType =
      std::make_shared<NoteType>("ankicpp::Basic_and_Reversed");
  noteType->addTemplate(basicTemplate);
  noteType->addTemplate(reversedTemplate);
  noteType->setStyle(style);
  noteType->setHeader(header);
  noteType->setFooter(footer);
  std::shared_ptr<Field> frontField = std::make_shared<Field>("Front");
  frontField->setFont("Arial");
  frontField->setFontSize(20);
  noteType->addField(frontField);
  std::shared_ptr<Field> backField = std::make_shared<Field>("Back");
  backField->setFont("Arial");
  backField->setFontSize(20);
  noteType->addField(backField);
  return noteType;
}();

const std::shared_ptr<Template> clozeTemplate = []() {
  const std::shared_ptr<Template> templatee =
      std::make_shared<Template>("ankicpp::Cloze::Card_1");
  templatee->setFrontTemplate("{{cloze:Text}}");
  templatee->setBackTemplate(R"({{cloze:Text}}<br>
{{Back Extra}})");
  return templatee;
}();

const std::string clozeStyle = R"(.card {
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
)";

const std::shared_ptr<NoteType> clozeNoteType = []() {
  const std::shared_ptr<NoteType> noteType =
      std::make_shared<NoteType>("ankicpp::Cloze");
  noteType->addTemplate(clozeTemplate);
  noteType->setStyle(clozeStyle);
  noteType->setHeader(header);
  noteType->setFooter(footer);
  std::shared_ptr<Field> textField = std::make_shared<Field>("Text");
  textField->setFont("Arial");
  textField->setFontSize(20);
  noteType->addField(textField);
  std::shared_ptr<Field> backField = std::make_shared<Field>("Back Extra");
  backField->setFont("Arial");
  backField->setFontSize(20);
  noteType->addField(backField);
  return noteType;
}();
} // namespace ankicpp
