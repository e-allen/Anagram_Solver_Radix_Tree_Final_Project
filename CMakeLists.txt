cmake_minimum_required(VERSION 3.10)

project(AnagramSolver)

configure_file(code/scrabble_dictionary.txt scrabble_dictionary.txt COPYONLY)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Google Test ---
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)
# --- End Google Test ---

# --- Main Application ---
include_directories(code)
add_executable(anagram_solver app/main.cpp code/Radix.cpp)
# --- End Main Application ---


# --- Tests ---
enable_testing()

add_executable(run_tests tests/test.cpp code/Radix.cpp)

target_compile_definitions(run_tests PRIVATE TESTING)

target_link_libraries(run_tests GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(run_tests)
# --- End Tests ---