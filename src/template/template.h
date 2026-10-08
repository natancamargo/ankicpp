#pragma once

#include "template/template-dto.h"
#include "template/template-repository.h"
#include "util/identifyable.h"
#include "util/nameable.h"
#include <cstdint>
#include <memory>
#include <string>

namespace ankicpp {
class NoteType;
class Template : public Identifyable, public Nameable {
public:
  Template(std::string name);

  std::string getFrontTemplate() const;
  void setFrontTemplate(std::string frontTemplate);

  std::string getBackTemplate() const;
  void setBackTemplate(std::string backTemplate);

  std::weak_ptr<NoteType> getNoteType();
  void setNoteType(std::weak_ptr<NoteType> noteType);

private:
  std::string _frontTemplate;
  std::string _backTemplate;
  std::weak_ptr<NoteType> _noteType;
};
} // namespace ankicpp
