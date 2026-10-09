#pragma once

#include "deck/deck.h"
#include <functional>
#include <soci/soci.h>
namespace ankicpp {
namespace database {
extern soci::session sql;
bool connect(std::string filename);
bool createDatabase();
bool populateDatabase(const std::shared_ptr<Deck> &deck);
bool disconnect();
bool safeSql(std::function<void(void)> function);
} // namespace database
} // namespace ankicpp
