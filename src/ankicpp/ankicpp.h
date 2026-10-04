#pragma once

#include "ankicpp/config-lib.h"
#include "ankicpp/export.h"
#include "card/card.h"
#include "compression/compression.h"
#include "database/database.h"
#include "deck/deck.h"
#include "field/field.h"
#include "note/note.h"
#include "util/util.h"

#include <iostream>

namespace ankicpp {
int initialized = []() {
  std::cout << std::format("================\n{}@{}\n================\n",
                           project_name, project_version);
  return 0;
 }();
} // namespace ankicpp
