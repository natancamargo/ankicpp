cmake_minimum_required(VERSION 3.5.0)
project(ankicpp VERSION 1.0.0)

include(FetchContent)

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
    -Wno-enum-compare
    -Wno-error=maybe-uninitialized
  )
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  add_compile_options(/W4)
endif()

# dependencies
# ----------------------------------------------------------------------------------------
# versions
set(CATCH2_VERSION v3.5.3)
set(ZLIB_VERSION v1.3.2)
set(ZSTD_VERSION v1.5.7)
set(SOCI_VERSION v4.1.4)

# dependency: catch2
if(ENABLE_TEST)
    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2
        GIT_TAG ${CATCH2_VERSION}
        GIT_SHALLOW TRUE)
    FetchContent_MakeAvailable(Catch2)
endif()


# dependency: zlib
set(ZLIB_BUILD_MINIZIP true CACHE BOOL "Build minizip")
set(MINIZIP_BUILD_STATIC true CACHE BOOL "Build minizip staticly")
FetchContent_Declare(
    zlib
    GIT_REPOSITORY https://github.com/madler/zlib
    GIT_TAG ${ZLIB_VERSION}
    GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(zlib)

# dependency: zstd
FetchContent_Declare(
    zstd
    GIT_REPOSITORY https://github.com/facebook/zstd
    GIT_TAG ${ZSTD_VERSION}
    GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(zstd)

# dependency: soci
FetchContent_Declare(
    soci
    GIT_REPOSITORY https://github.com/SOCI/soci
    GIT_TAG ${SOCI_VERSION}
    GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(soci)

# target library
# ----------------------------------------------------------------------------------------
set(LIBRARY_NAME ankicpp)
add_library(${LIBRARY_NAME} STATIC
  "${CMAKE_SOURCE_DIR}/src/card/card-repository.cc"
  "${CMAKE_SOURCE_DIR}/src/card/card.cc"

  "${CMAKE_SOURCE_DIR}/src/compression/compression.cc"
  "${CMAKE_SOURCE_DIR}/src/compression/zip-utils.cc"
  "${CMAKE_SOURCE_DIR}/src/compression/zstd-utils.cc"

  "${CMAKE_SOURCE_DIR}/src/database/database.cc"

  "${CMAKE_SOURCE_DIR}/src/deck/deck.cc"

  "${CMAKE_SOURCE_DIR}/src/field/field.cc"

  "${CMAKE_SOURCE_DIR}/src/ankicpp/export.cc"

  "${CMAKE_SOURCE_DIR}/src/note/note-type.cc"
  "${CMAKE_SOURCE_DIR}/src/note/note.cc"

  "${CMAKE_SOURCE_DIR}/src/template/template.cc"

  "${CMAKE_SOURCE_DIR}/src/util/nameable.cc"
  "${CMAKE_SOURCE_DIR}/src/util/identifyable.cc"
  "${CMAKE_SOURCE_DIR}/src/util/time.cc"
)
target_link_libraries(${LIBRARY_NAME} PUBLIC
  MINIZIP::minizipstatic
  zstd
  SOCI::SOCI
  SOCI::SQLite3
)
target_include_directories(${LIBRARY_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/src")

# target executable
# ----------------------------------------------------------------------------------------
set(EXECUTABLE_NAME exe)
add_executable(${EXECUTABLE_NAME}
  "${CMAKE_SOURCE_DIR}/src/main.cc"
)
target_link_libraries(${EXECUTABLE_NAME} PUBLIC ${LIBRARY_NAME})
set_target_properties(${EXECUTABLE_NAME} PROPERTIES
RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})
set_property(TARGET ${EXECUTABLE_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:${PROJECT_NAME}>)

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
  TARGET ${EXECUTABLE_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/src/database/schema11.sql $<TARGET_FILE_DIR:${EXECUTABLE_NAME}>/database/schema11.sql
)
