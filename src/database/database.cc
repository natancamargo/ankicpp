#include "database/database.h"
#include <fstream>
#include <iostream>
#include <soci/soci.h>
#include <soci/sqlite3/soci-sqlite3.h>

namespace ankicpp {
namespace database {
soci::session sql;
bool connect(std::string filename) {
  try {
    sql = soci::session(soci::sqlite3, filename.data());
  } catch (soci::sqlite3_soci_error const &e) {
    std::cout << "SQLite3 error " << e.what() << ", error code: " << e.result()
              << std::endl;
    return false;
  } catch (soci::soci_error const &e) {
    std::cout << "SOCI error: " << e.what() << std::endl;
    return false;
  }
  return true;
}
bool createDatabase() {
  std::ifstream inStream = std::ifstream{"database/schema11.sql"};
  if (!inStream.is_open()) {
    perror("Error while opening the database ddl.\n");
    return false;
  }

  std::stringstream buffer = std::stringstream{};
  if (inStream) {

    try {
      inStream.exceptions(inStream.failbit | inStream.badbit);
      buffer << inStream.rdbuf();
    } catch (const std::ifstream::failure &e) {
      std::cout << std::format("Error:\n{}\nError code: {}\n", e.what(),
                               e.code().value());
      inStream.close();
      return false;
    }

    try {
      sql << buffer.str();
      if (errno) {
        errno = 0;        
      }        
    } catch (soci::sqlite3_soci_error const &e) {
      std::cout << "SQLite3 error " << e.what()
                << ", error code: " << e.result() << std::endl;
      inStream.close();
      return false;
    } catch (soci::soci_error const &e) {
      std::cout << "SOCI error: " << e.what() << std::endl;
      inStream.close();
      return false;
    }
  }
  inStream.close();

  return true;
}
bool populateDatabase(Deck deck) { return true; }
bool disconnect() { return true; }
} // namespace database
} // namespace ankicpp
