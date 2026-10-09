cmake_minimum_required(VERSION 3.5.0)
project(ankicpp VERSION 0.0.3)

# enable unit tests
option(ENABLE_TEST "Enable unit testing" ON)

# generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# c standard
# ----------------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD          20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)

# compile options
# ----------------------------------------------------------------------------------------
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU") 
  add_compile_options(
    -Wall
    -Wpedantic
    -Wextra
    -Werror
  )
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  add_compile_options(/W4)
endif()

# dependencies
# ----------------------------------------------------------------------------------------
set (VCPKG_DIR ${CMAKE_SOURCE_DIR}/external/vcpkg)
include(${VCPKG_DIR}/scripts/buildsystems/vcpkg.cmake)

find_package(minizip CONFIG REQUIRED)
find_package(Catch2 CONFIG REQUIRED)
find_package(zstd CONFIG REQUIRED)
find_package(soci CONFIG REQUIRED)
find_package(unofficial-sqlite3 REQUIRED
find_package(uuid CONFIG REQUIRED))

# target library
# ----------------------------------------------------------------------------------------
set(LIBRARY_NAME ankicpp)
add_library(${LIBRARY_NAME} STATIC
  "${CMAKE_SOURCE_DIR}/src/card/card-mapper.cc"
  "${CMAKE_SOURCE_DIR}/src/card/card-repository.cc"
  "${CMAKE_SOURCE_DIR}/src/card/card.cc"

  "${CMAKE_SOURCE_DIR}/src/col/col-repository.cc"

  "${CMAKE_SOURCE_DIR}/src/compression/compression.cc"
  "${CMAKE_SOURCE_DIR}/src/compression/zip-utils.cc"
  "${CMAKE_SOURCE_DIR}/src/compression/zstd-utils.cc"

  "${CMAKE_SOURCE_DIR}/src/config/config-repository.cc"

  "${CMAKE_SOURCE_DIR}/src/database/database.cc"

  "${CMAKE_SOURCE_DIR}/src/deck/deck.cc"
  "${CMAKE_SOURCE_DIR}/src/deck/deck-mapper.cc"
  "${CMAKE_SOURCE_DIR}/src/deck/deck-repository.cc"
  "${CMAKE_SOURCE_DIR}/src/deck/deck-config-repository.cc"

  "${CMAKE_SOURCE_DIR}/src/field/field.cc"
  "${CMAKE_SOURCE_DIR}/src/field/field-mapper.cc"
  "${CMAKE_SOURCE_DIR}/src/field/field-repository.cc"

  "${CMAKE_SOURCE_DIR}/src/ankicpp/export.cc"

  "${CMAKE_SOURCE_DIR}/src/note/note-type.cc"
  "${CMAKE_SOURCE_DIR}/src/note/note-type-mapper.cc"
  "${CMAKE_SOURCE_DIR}/src/note/note-type-repository.cc"
  "${CMAKE_SOURCE_DIR}/src/note/note.cc"
  "${CMAKE_SOURCE_DIR}/src/note/note-mapper.cc"
  "${CMAKE_SOURCE_DIR}/src/note/note-repository.cc"

  "${CMAKE_SOURCE_DIR}/src/template/template.cc"
  "${CMAKE_SOURCE_DIR}/src/template/template-mapper.cc"
  "${CMAKE_SOURCE_DIR}/src/template/template-repository.cc"

  "${CMAKE_SOURCE_DIR}/src/util/nameable.cc"
  "${CMAKE_SOURCE_DIR}/src/util/identifyable.cc"
  "${CMAKE_SOURCE_DIR}/src/util/time.cc"
)
target_link_libraries(${LIBRARY_NAME} PUBLIC
  MINIZIP::minizipstatic
  zstd::libzstd
  SOCI::SOCI
  unofficial::sqlite3::sqlite3
  uuid
)
target_include_directories(${LIBRARY_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/src")

# target tests
# ----------------------------------------------------------------------------------------
set(TEST_NAME "unit-tests")

add_executable(${TEST_NAME}
  "${CMAKE_SOURCE_DIR}/tests/main.cc"
)
target_link_libraries(${TEST_NAME} PUBLIC ${LIBRARY_NAME} Catch2::Catch2WithMain)
set_target_properties(${TEST_NAME} PROPERTIES
RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})
set_property(TARGET ${TEST_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:${PROJECT_NAME}>)

# config file
# ----------------------------------------------------------------------------------------
configure_file(
  "${CMAKE_SOURCE_DIR}/src/ankicpp/config-lib.h.in"
  "${CMAKE_BINARY_DIR}/ankicpp/config-lib.h" ESCAPE_QUOTES
)
target_include_directories(${LIBRARY_NAME} PUBLIC "${CMAKE_BINARY_DIR}")

# docs
# ----------------------------------------------------------------------------------------
add_custom_target(docs
    COMMAND doxygen doxygen
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Generating HTML documentation with Doxygen"
)

# copy resources
# ----------------------------------------------------------------------------------------
add_custom_command(
  TARGET ${LIBRARY_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/src/database/schema.sql ${CMAKE_BINARY_DIR}/${PROJECT_NAME}/database/schema.sql
)
