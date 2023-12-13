
cmake_minimum_required(VERSION 3.20)
project(cpp-sudoku)

set(SOURCES src/sudoku.cpp)

option(BUILD_SHARED_LIBS "Build as shared library" OFF)
if(BUILD_SHARED_LIBS)
    add_library(cpp-sudoku SHARED ${SOURCES})
else()
    add_library(cpp-sudoku STATIC ${SOURCES})
endif()

target_compile_features(cpp-sudoku PUBLIC cxx_std_17)
target_include_directories(cpp-sudoku PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)


# Tests
option(BUILD_TESTS "Build tests" ON)

if(BUILD_TESTS)
    add_executable(sudoku_tests tests/sudoku_test.cpp)
    target_link_libraries(sudoku_tests PRIVATE cpp-sudoku)
endif()
