cmake_minimum_required(VERSION 3.5.0)
project(ankicpp VERSION 1.0.0)

include(FetchContent)

# build type and others
# ----------------------------------------------------------------------------------------
set(CMAKE_BUILD_TYPE Debug)

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

# dependency: raylib
#FetchContent_Declare(
#  raylib
#  GIT_REPOSITORY https://github.com/raysan5/raylib
#  GIT_TAG ${RAYLIB_VERSION}
#  GIT_SHALLOW TRUE
#)
#FetchContent_MakeAvailable(raylib)

# dependency: catch2
if(ENABLE_TEST)
    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2
        GIT_TAG ${CATCH2_VERSION}
        GIT_SHALLOW TRUE)
    FetchContent_MakeAvailable(Catch2)
endif()

# target library
# ----------------------------------------------------------------------------------------
set(LIBRARY_NAME ankicpp)
add_library(${LIBRARY_NAME} STATIC
  "${CMAKE_SOURCE_DIR}/src/card/card-type.cc"
  "${CMAKE_SOURCE_DIR}/src/card/card.cc"

  "${CMAKE_SOURCE_DIR}/src/deck/deck.cc"

  "${CMAKE_SOURCE_DIR}/src/field/field.cc"

  "${CMAKE_SOURCE_DIR}/src/lib/export.cc"

  "${CMAKE_SOURCE_DIR}/src/note/note-type.cc"
  "${CMAKE_SOURCE_DIR}/src/note/note.cc"

  "${CMAKE_SOURCE_DIR}/src/util/time.cc"
)
target_link_libraries(${LIBRARY_NAME} PUBLIC)
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

# config file
# ----------------------------------------------------------------------------------------
configure_file(
  "${CMAKE_SOURCE_DIR}/src/lib/config-lib.h.in"
  "${CMAKE_BINARY_DIR}/lib/config-lib.h" ESCAPE_QUOTES
)
target_include_directories(${LIBRARY_NAME} PUBLIC "${CMAKE_BINARY_DIR}")
