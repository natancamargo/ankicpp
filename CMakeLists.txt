cmake_minimum_required(VERSION 3.10.0)
project(ankicpp VERSION 0.1.19)

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
#set (VCPKG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/vcpkg)
#include(${VCPKG_DIR}/scripts/buildsystems/vcpkg.cmake)
include($ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)

find_package(minizip CONFIG REQUIRED)
find_package(Catch2 CONFIG REQUIRED)
find_package(zstd CONFIG REQUIRED)
find_package(soci CONFIG REQUIRED)
find_package(unofficial-sqlite3 REQUIRED)
find_package(Protobuf REQUIRED)
find_package(OpenSSL REQUIRED)

# target library
# ----------------------------------------------------------------------------------------
set(LIBRARY_NAME ankicpp)
add_library(${LIBRARY_NAME} STATIC
  "${CMAKE_CURRENT_SOURCE_DIR}/src/card/card-mapper.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/card/card-repository.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/card/card.cc"

  "${CMAKE_CURRENT_SOURCE_DIR}/src/col/col-repository.cc"

  "${CMAKE_CURRENT_SOURCE_DIR}/src/compression/zip-utils.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/compression/zstd-utils.cc"

  "${CMAKE_CURRENT_SOURCE_DIR}/src/config/config-repository.cc"

  "${CMAKE_CURRENT_SOURCE_DIR}/src/database/database.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/database/ddl.cc"

  "${CMAKE_CURRENT_SOURCE_DIR}/src/deck/deck.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/deck/deck-mapper.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/deck/deck-repository.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/deck/deck-config-repository.cc"

  "${CMAKE_CURRENT_SOURCE_DIR}/src/field/field.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/field/field-mapper.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/field/field-repository.cc"

  "${CMAKE_CURRENT_SOURCE_DIR}/src/ankicpp/export.cc"

  "${CMAKE_CURRENT_SOURCE_DIR}/src/note/note-type.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/note/note-type-mapper.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/note/note-type-repository.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/note/note.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/note/note-mapper.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/note/note-repository.cc"

  "${CMAKE_CURRENT_SOURCE_DIR}/src/template/template.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/template/template-mapper.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/template/template-repository.cc"

  "${CMAKE_CURRENT_SOURCE_DIR}/src/util/nameable.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/util/identifyable.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/util/time.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/util/crypto.cc"

  "${CMAKE_CURRENT_SOURCE_DIR}/resources/proto/meta.proto"
  "${CMAKE_CURRENT_SOURCE_DIR}/resources/proto/media.proto"
  "${CMAKE_CURRENT_SOURCE_DIR}/resources/proto/note-type.proto"
)
target_link_libraries(${LIBRARY_NAME} PUBLIC
  MINIZIP::minizipstatic
  zstd::libzstd
  SOCI::SOCI
  unofficial::sqlite3::sqlite3
  OpenSSL::SSL
  protobuf::libprotobuf
)
target_include_directories(${LIBRARY_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

# target tests
# ----------------------------------------------------------------------------------------
set(TEST_NAME "unit-tests")

add_executable(${TEST_NAME}
  "${CMAKE_CURRENT_SOURCE_DIR}/tests/main.cc"
)
target_link_libraries(${TEST_NAME} PUBLIC ${LIBRARY_NAME} Catch2::Catch2WithMain)
set_target_properties(${TEST_NAME} PROPERTIES
RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME})
set_property(TARGET ${TEST_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:${PROJECT_NAME}>)

# config file
# ----------------------------------------------------------------------------------------
configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/src/ankicpp/config-lib.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/ankicpp/config-lib.h" ESCAPE_QUOTES
)
target_include_directories(${LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

# docs
# ----------------------------------------------------------------------------------------
add_custom_target(docs
    COMMAND doxygen doxygen
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Generating HTML documentation with Doxygen"
)

# create and copy resources
# ----------------------------------------------------------------------------------------
# copy file
add_custom_command(
  TARGET ${TEST_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/resources/images ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/images
)
# create testing directories
add_custom_command(
  TARGET ${TEST_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/empty
  COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/basic
  COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/basic-and-reversed
  COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/tags
  COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/cloze
  COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/nested
  COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/media
)

# protobuf
# ----------------------------------------------------------------------------------------
if(Protobuf_FOUND)
  protobuf_generate(TARGET ${LIBRARY_NAME})
endif()

target_include_directories(${LIBRARY_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

# install
# ----------------------------------------------------------------------------------------
install(TARGETS ${LIBRARY_NAME} LIBRARY DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(CMAKE_CONFIG_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/ankicpp")

configure_package_config_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/ankicppConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/ankicppConfig.cmake
  INSTALL_DESTINATION
    ${CMAKE_CONFIG_DESTINATION}
)

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/ankicppConfigVersion.cmake"
  COMPATIBILITY
    SameMajorVersion
)

install(
  FILES
    "${CMAKE_CURRENT_BINARY_DIR}/ankicppConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/ankicppConfigVersion.cmake"
  DESTINATION
    ${CMAKE_CONFIG_DESTINATION}
)

install(EXPORT ankicpp-targets
    FILE ankicpp-targets.cmake
    NAMESPACE ankicpp::
    DESTINATION ${CMAKE_CONFIG_DESTINATION}
    COMPONENT ankicpp_development
)
