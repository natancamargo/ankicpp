#include "database/database.h"
#include "ankicpp/export.h"
#include "card/card-dto.h"
#include "card/card-mapper.h"
#include "card/card-repository.h"
#include "col/col-dto.h"
#include "col/col-repository.h"
#include "config/config-dto.h"
#include "config/config-repository.h"
#include "deck/deck-config-dto.h"
#include "deck/deck-config-repository.h"
#include "database/repository.h"
#include "deck/deck-dto.h"
#include "deck/deck-repository.h"
#include "deck/deck-mapper.h"
#include "note/note-mapper.h"
#include "note/note-repository.h"
#include "note/note-type-dto.h"
#include "note/note-type-mapper.h"
#include "note/note-type-repository.h"
#include "field/field-repository.h"
#include "template/template-dto.h"
#include "template/template.h"
#include "template/template-mapper.h"
#include "field/field-mapper.h"
#include <cerrno>
#include <cstdint>
#include <format>
#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <ostream>
#include <soci/soci.h>
#include <soci/sqlite3/soci-sqlite3.h>
#include <sqlite3.h>

namespace ankicpp {
namespace database {
soci::session sql;
sqlite3 *db;
bool connect(std::string filename) {
  int connectionOpened = safeSql(
      [filename]() { sql = soci::session(soci::sqlite3, filename.data()); });
  if (!connectionOpened) {
    return false;    
  }
  int connectionError = sqlite3_open(filename.data(), &db);
  if (connectionError) {
    error = Error::EXPORT_DATABASE_ERROR;
    std::cout << std::format(
        "database: sql3lite database could not be opened {} \n",
        sqlite3_errmsg(db));
  }

  return true;
}
bool createDatabase() {
  std::ifstream inStream = std::ifstream{"database/schema.sql"};
  if (!inStream.is_open()) {
    error = Error::EXPORT_DATABASE_ERROR;
    perror("database: Error while opening the database ddl.\n");
    return false;
  }

  std::stringstream ddlBuffer = std::stringstream{};
  if (inStream) {

    try {
      inStream.exceptions(inStream.failbit | inStream.badbit);
      ddlBuffer << inStream.rdbuf();
    } catch (const std::ifstream::failure &e) {
      error = Error::EXPORT_DATABASE_ERROR;
      std::cout << std::format("database: Error:\n{}\nError code: {}\n",
                               e.what(), e.code().value());
      inStream.close();
      return false;
    }
    char *errorMsg;
    int rc = sqlite3_exec(db, ddlBuffer.str().c_str(), NULL, 0, &errorMsg);
    if (rc != SQLITE_OK) {
      error = Error::EXPORT_DATABASE_ERROR;
      std::cout << std::format("database: Error: {}\n", errorMsg);
      std::cout << "database: Error in executing ddl\n";
      sqlite3_free(errorMsg);
      return false;
    }
  }
  inStream.close();

  return true;
}
bool populateDatabase(Deck deck) {
  const Repository<DeckDTO, std::int64_t> &deckRepository = DeckRepository();
  const Repository<CardDTO, std::int64_t> &cardRepository = CardRepository();
  const Repository<TemplateDTO, std::int64_t> &templateRepository = TemplateRepository();
  const Repository<FieldDTO, std::int64_t> &fieldRepository = FieldRepository();
  const Repository<NoteDTO, std::int64_t> &noteRepository = NoteRepository();
  const Repository<NoteTypeDTO, std::int64_t> &noteTypeRepository = NoteTypeRepository();
  const Repository<ColDTO, std::int64_t> &colRepository = ColRepository();
  const Repository<ConfigDTO, std::int64_t> &configRepository = ConfigRepository();
  const Repository<DeckConfigDTO, std::int64_t> &deckConfigRepository = DeckConfigRepository();

  // deck
  deckRepository.create(deckMapper::modelToDTO(deck));

  // col  
  colRepository.create(ColDTO::createDTO());
  
  // Config
  const std::vector<ConfigDTO> configDTOs = ConfigDTO::createDTOs();
  for (const ConfigDTO &configDTO : configDTOs) {
    configRepository.create(configDTO);
  }

  // Deck config
  deckConfigRepository.create(DeckConfigDTO::createDefaultDTO());
  deckRepository.create(DeckDTO::createDefaultDTO());
  
  for (const std::shared_ptr<Note> &note : deck.getNotes()) {
    const NoteDTO noteDTO = noteMapper::modelToDTO(*note);
    noteRepository.create(noteDTO);
    
    const std::shared_ptr<NoteType> &noteType = note->getType();
    const NoteTypeDTO noteTypeDTO = noteTypeMapper::modelToDTO(*noteType);
    noteTypeRepository.create(noteTypeDTO);
    
    // Templates
    for (const std::shared_ptr<Template> &templatee :
         noteType->getTemplates()) {
      const std::shared_ptr<Card> &card = std::make_shared<Card>();
      card->setDeck(std::make_shared<Deck>(deck));
      card->setNote(note);
      card->setTemplate(templatee);
      const CardDTO cardDTO = cardMapper::modelToDTO(*card);
      const TemplateDTO templateDTO = templateMapper::modelToDTO(*templatee);
      cardRepository.create(cardDTO);
      templateRepository.create(templateDTO);
    }

    // Fields
    for (const std::shared_ptr<Field> &field : noteType->getFields()) {
      const FieldDTO fieldDTO = fieldMapper::modelToDTO(*field);
      fieldRepository.create(fieldDTO);
     }
  }

  return true;
}
bool disconnect() {
  sql.close();
  sqlite3_close(db);
  return true;
}
bool safeSql(std::function<void(void)> function) {
  try {
    function();
  } catch (soci::sqlite3_soci_error const &e) {
    error = Error::EXPORT_DATABASE_ERROR;
    std::cout << "database: SQLite3 error " << e.what()
              << ", error code: " << e.result() << std::endl;
    return false;
  } catch (soci::soci_error const &e) {
    error = Error::EXPORT_DATABASE_ERROR;
    std::cout << "database:  SOCI error: " << e.what() << std::endl;
    return false;
  }

  return true;
}
} // namespace database
} // namespace ankicpp
