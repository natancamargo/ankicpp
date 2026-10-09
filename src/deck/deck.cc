#include "deck/deck.h"
#include "ankicpp/export.h"
#include "note/note-type.h"
#include "util/nameable.h"
#include <cstddef>
#include <format>
#include <iostream>
#include <memory>
#include <regex>

namespace ankicpp {
using std::make_shared;

Deck::Deck(std::string name) : Nameable(name) {}

std::set<std::shared_ptr<Note>> &Deck::getNotes() { return _notes; }
void Deck::addNote(std::shared_ptr<Note> note) {
  _notes.insert(note);

  // Basic and reversed additional notes
  const std::shared_ptr<NoteType> &noteType = note->getType();
  if (!noteType) {
    error = Error::DATA_NOTE_WITHOUT_TYPE_ERROR;
    std::cout << std::format("export: note without type.\n");
    return;
  }
  // reversed
  const bool isBasicAndReversed = noteType == basicAndReversedNoteType;
  if (isBasicAndReversed) {
    const std::shared_ptr<Note> newNote = std::make_shared<Note>();
    newNote->setType(noteType);
    newNote->setTags(note->getTags());
    newNote->setFields(note->getFields());
    newNote->setFlags(note->getFlags());
    newNote->setReversedParent(note);
    _notes.insert(newNote);
  }
}
void Deck::removeNote(std::shared_ptr<Note> note) { _notes.erase(note); }

std::set<std::shared_ptr<Card>> &Deck::getCards() { return _cards; }
void Deck::addCard(std::shared_ptr<Card> card) {
  _cards.insert(card);
  card->setDeck(std::make_shared<Deck>(*this));
}
void Deck::removeCard(std::shared_ptr<Card> card) {
  _cards.erase(card);
  card->setDeck(nullptr);
}
void Deck::clearCards() { _cards.clear(); }

bool Deck::generateCards() {
  clearCards();
  const std::set<std::shared_ptr<Note>> &notes = getNotes();
  if (getNotes().size() == 0) {
    error = Error::DATA_DECK_EMPTY_ERROR;
    std::cout << std::format("data: deck without notes.\n");
    return false;
  }

  for (std::shared_ptr<Note> note : notes) {
    const std::shared_ptr<NoteType> &noteType = note->getType();
    if (!noteType) {
      error = Error::DATA_NOTE_WITHOUT_TYPE_ERROR;
      std::cout << std::format("data: note without type.\n");
      return false;
    }

    // Do not generate cards to reversed child
    const bool isReversedChild = !!note->getReversedParent();
    if (isReversedChild) {
      continue;
    }

    for (const std::shared_ptr<Template> &templatee :
         noteType->getTemplates()) {
      // 1 card per template per note
      const std::shared_ptr<Card> &card = std::make_shared<Card>();
      card->setNote(note);
      card->setOrder(noteType->getTemplateIndex(templatee));
      addCard(card);
    }

    // One card for each cloze expression
    const bool isCloze = noteType == clozeNoteType;
    if (isCloze) {
      const std::string &fielValue = note->getField("Text");
      std::regex clozeRegex("\\{\\{c\\d+::(.*?)\\}\\}");

      std::sregex_iterator clozeBegin =
          std::sregex_iterator(fielValue.begin(), fielValue.end(), clozeRegex);
      std::sregex_iterator clozeEnd = std::sregex_iterator();
      std::size_t clozes = std::distance(clozeBegin, clozeEnd);      
      for (std::size_t i = 1; i < clozes; i++) {
        const std::shared_ptr<Card> &card = make_shared<Card>();
        card->setNote(note);
        card->setOrder(i);
        addCard(card);
      }
    }
  }
  return true;
}
} // namespace ankicpp
