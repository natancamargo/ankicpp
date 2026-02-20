#include <catch2/catch_test_macros.hpp>

#include <map>
#include <string>

#include "lib/hello-world.h"

TEST_CASE("Lib should work properly", "[lib]") {
  REQUIRE_NOTHROW(helloWorld());
}
