#pragma once

#include <string>

namespace ankicpp {
  class NoteType;
  class CardType {
  public:
    CardType(std::string name);

    std::string getName() const;
    void setName(std::string name);

    std::string getFrontTemplate() const;
    void setFrontTemplate(std::string frontTemplate);

    std::string getBackTemplate() const;
    void setBackTemplate(std::string backTemplate);

    NoteType *getNoteType();
    void setNoteType(NoteType *noteType);
  private:
    std::string _name;
    std::string _frontTemplate;
    std::string _backTemplate;
    NoteType *_noteType;
  };
}
