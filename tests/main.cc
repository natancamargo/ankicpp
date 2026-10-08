#include <catch2/catch_test_macros.hpp>
#include <memory>

#include "ankicpp/ankicpp.h"
#include "note/note-type.h"

TEST_CASE("Note should work properly", "[note]") {
  ankicpp::Note note;
  SECTION("when setting fields", "[note]") {
    note.addField("Front", "some front text");
    note.addField("Back", "some back text");
    REQUIRE(note.getFields().size() == 2);
    note.removeField("Front");
    REQUIRE(note.getFields().size() == 1);
  }
  SECTION("when setting tags", "[note]") {
    note.addTag("Tag1");
    note.addTag("Tag2");
    REQUIRE(note.getTags().size() == 2);
    note.removeTag("Tag1");
    REQUIRE(note.getTags().size() == 1);
  }
  SECTION("when setting flags", "[note]") {
    note.setFlags(3);
    REQUIRE(note.getFlags() == 3);
  }
  SECTION("when setting note-type", "[note][note-type]") {
    note.setType(ankicpp::basicNoteType);
    REQUIRE(note.getType() == ankicpp::basicNoteType);
  }
}

TEST_CASE("NoteType should work properly", "[note-type]") {
  std::shared_ptr<ankicpp::NoteType> noteType =
      std::make_shared<ankicpp::NoteType>("note-type name");
  SECTION("when setting fields", "[note-type][field]") {
    std::shared_ptr<ankicpp::Field> fieldFront =
        std::make_shared<ankicpp::Field>("Front");
    std::shared_ptr<ankicpp::Field> fieldBack =
        std::make_shared<ankicpp::Field>("Back");
    noteType->addField(fieldFront);
    noteType->addField(fieldBack);
    REQUIRE(noteType->getFields().size() == 2);
    noteType->addField(fieldFront);
    REQUIRE(noteType->getFields().size() == 2);
    noteType->removeField(fieldBack);
    REQUIRE(noteType->getFields().size() == 1);
  }
  SECTION("when setting templates", "[note-type][template]") {
    std::shared_ptr<ankicpp::Template> template1 =
        std::make_shared<ankicpp::Template>("Template 1");
    std::shared_ptr<ankicpp::Template> template2 =
        std::make_shared<ankicpp::Template>("Template 1");
    noteType->addTemplate(template1);
    noteType->addTemplate(template2);
    REQUIRE(noteType->getTemplates().size() == 2);
    noteType->removeTemplate(template2);
    REQUIRE(noteType->getTemplates().size() == 1);
  }
  SECTION("when checking predefined note types", "[note-type][template]") {
    REQUIRE(ankicpp::basicNoteType->getFields().size() == 2);
    REQUIRE(ankicpp::basicNoteType->getTemplates().size() == 1);
    REQUIRE(ankicpp::clozeNoteType->getFields().size() == 2);
    REQUIRE(ankicpp::clozeNoteType->getTemplates().size() == 1);
  }
}

TEST_CASE("Deck should work properly", "[deck]") {
  ankicpp::Deck deck{"deck-name"};
  SECTION("when setting notes", "[deck][note]") {
    std::shared_ptr<ankicpp::Note> note1 = std::make_shared<ankicpp::Note>();
    std::shared_ptr<ankicpp::Note> note2 = std::make_shared<ankicpp::Note>();
    note1->setType(ankicpp::basicNoteType);    
    note2->setType(ankicpp::basicNoteType);    
    deck.addNote(note1);
    deck.addNote(note2);
    REQUIRE(deck.getNotes().size() == 2);
    deck.removeNote(note2);
    REQUIRE(deck.getNotes().size() == 1);
  }
  SECTION("when setting cards", "[deck][card]") {
    std::shared_ptr<ankicpp::Card> card1 = std::make_shared<ankicpp::Card>();
    std::shared_ptr<ankicpp::Card> card2 = std::make_shared<ankicpp::Card>();
    deck.addCard(card1);
    deck.addCard(card2);
    REQUIRE(deck.getCards().size() == 2);
    deck.removeCard(card2);
    REQUIRE(deck.getCards().size() == 1);
    deck.clearCards();
    REQUIRE(deck.getCards().size() == 0);
  }
  SECTION("when setting a complete basic note", "[deck][card]") {
    std::shared_ptr<ankicpp::Note> note = std::make_shared<ankicpp::Note>();

    note->setType(ankicpp::basicNoteType);
    note->addField("Front", "<Front Content>");
    note->addField("Back", "<Back Content>");

    deck.addNote(note);
    deck.generateCards();

    REQUIRE(deck.getNotes().size() == 1);
    REQUIRE(deck.getCards().size() == 1);
    REQUIRE(note->getFields().size() == 2);
    REQUIRE(note->getType()->getFields().size() == 2);
    REQUIRE(note->getType()->getTemplates().size() == 1);
  }

  SECTION("when setting a complete basic and reversed note", "[deck][card]") {
    std::shared_ptr<ankicpp::Note> note = std::make_shared<ankicpp::Note>();

    note->setType(ankicpp::basicAndReversedNoteType);
    note->addField("Front", "<Front Content>");
    note->addField("Back", "<Back Content>");

    deck.addNote(note);
    deck.generateCards();

    REQUIRE(deck.getNotes().size() == 2);
    REQUIRE(deck.getCards().size() == 2);
    REQUIRE(note->getFields().size() == 2);
    REQUIRE(note->getType()->getFields().size() == 2);
    REQUIRE(note->getType()->getTemplates().size() == 2);
  }
}

TEST_CASE("Export should work properly", "[export]") {
  ankicpp::Deck deck{"deck-name"};
  SECTION("when trying to export an empty deck it should fail",
          "[deck][export]") {
    REQUIRE(ankicpp::exportDeck(deck, "./empty/empty-deck.apkg") == false);
  }

  SECTION("when trying to export a basic deck", "[deck][export]") {
    ankicpp::Deck deck{"basic-deck"};    
    std::shared_ptr<ankicpp::Note> note = std::make_shared<ankicpp::Note>();

    note->setType(ankicpp::basicNoteType);
    note->addField("Front", "Front content");
    note->addField("Back", "Back content");

    deck.addNote(note);

    REQUIRE(ankicpp::exportDeck(deck, "./basic/deck.apkg"));
  }

  SECTION("when trying to export a basic and reversed deck", "[deck][export]") {
    ankicpp::Deck deck{"reversed-deck"};
    std::shared_ptr<ankicpp::Note> note = std::make_shared<ankicpp::Note>();

    note->setType(ankicpp::basicAndReversedNoteType);
    note->addField("Front", "<Front Content>");
    note->addField("Back", "<Back Content>");

    deck.addNote(note);

    REQUIRE(ankicpp::exportDeck(deck, "./basic-and-reversed/deck.apkg"));
  }
}
