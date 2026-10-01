#pragma once

#include <string_view>
#include "compression/zlib-utils.h"

namespace ankicpp {
  void compress(std::string_view filename);
}
