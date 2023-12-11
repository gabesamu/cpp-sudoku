
cmake_minimum_required(VERSION 3.20)
project(cpp-sudoku)

include_directories(include)

add_executable(sudoku main.cpp src/sudoku.cpp)

set_target_properties(sudoku PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON
)

set_source_files_properties(src/sudoku.cpp PROPERTIES
  COMPILE_FLAGS "-std=c++17"
)
