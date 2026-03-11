#include <catch2/catch_test_macros.hpp>

#include "lib/ankicpp.h"

TEST_CASE("Note should work properly", "[note]") {
  ankicpp::Note note;
  SECTION("when created", "[note]") {
    REQUIRE(note.getId() != 0);
  }
  SECTION("when setting fields", "[note]") {
    note.addField("front", "some front text");
    note.addField("back", "some back text");
    REQUIRE(note.getFields().size() == 2);
    note.removeField("front");
    REQUIRE(note.getFields().size() == 1);
  }
  SECTION("when setting tags", "[note]") {
    note.addTag("tag1");
    note.addTag("tag2");
    REQUIRE(note.getTags().size() == 2);
    note.removeTag("tag1");
    REQUIRE(note.getTags().size() == 1);
  }
  SECTION("when setting flags", "[note]") {
    note.setFlags(3);
    REQUIRE(note.getFlags() == 3);
  }
  SECTION("when setting note-type", "[note][note-type]") {
    note.setType(ankicpp::BasicNoteType);
    REQUIRE(note.getType() == ankicpp::BasicNoteType);
  }
}

TEST_CASE("NoteType should work properly", "[note-type]") {
  ankicpp::NoteType noteType{"note-type name"};
  SECTION("when created", "[note-type]") {
    REQUIRE(noteType.getId() != 0);
  }
  SECTION("when setting fields", "[note-type][field]") {
    ankicpp::Field fieldFront{"Front"};
    ankicpp::Field fieldBack{"Back"};
    noteType.addField(&fieldFront);
    noteType.addField(&fieldBack);
    REQUIRE(noteType.getFields().size() == 2);
    noteType.addField(&fieldFront);
    REQUIRE(noteType.getFields().size() == 2);
    noteType.removeField(&fieldBack);
    REQUIRE(noteType.getFields().size() == 1);
  }
  SECTION("when setting card-types", "[note-type][card-type]") {
    ankicpp::CardType card1{"Card 1"};
    ankicpp::CardType card2{"Card 2"};
    noteType.addCardType(&card1);
    noteType.addCardType(&card2);
    REQUIRE(noteType.getCardTypes().size() == 2);
    noteType.removeCardType(&card2);
    REQUIRE(noteType.getCardTypes().size() == 1);
  }
}

TEST_CASE("Deck should work properly", "[deck]") {
  ankicpp::Deck deck{"deck-name"};
  SECTION("when created", "[deck]") {
    REQUIRE(deck.getId() != 0);
  }
  SECTION("when setting notes", "[deck][note]") {
    ankicpp::Note note1;
    ankicpp::Note note2;
    deck.addNote(&note1);
    deck.addNote(&note2);
    REQUIRE(deck.getNotes().size() == 2);
    deck.removeNote(&note2);
    REQUIRE(deck.getNotes().size() == 1);
  }
  SECTION("when setting cards", "[deck][card]") {
    ankicpp::Card card1;
    ankicpp::Card card2;
    deck.addCard(&card1);
    deck.addCard(&card2);
    REQUIRE(deck.getCards().size() == 2);
    deck.removeCard(&card2);
    REQUIRE(deck.getCards().size() == 1);
    deck.clearCards();
    REQUIRE(deck.getCards().size() == 0);
  }
}
