# Cpp-sudoku

---

* `sudoku.cpp/.hpp`: Solver class with methods for parsing boards as strings, solving parsed boards, and pretty printing as strings.
The alogorithm used is constraint propagation with backtracking search. The algorithm is described in detail by Peter Norvig [here](http://norvig.com/sudoku.html).



# Building

## prerequisites

Before building `cpp-sudoku`, ensure you have the following installed:
- CMake (version 3.20 or higher)
- A modern C++ compiler that supports at least C++17

## clone and build

The default build is a static library. To build as dynamic set the `BUILD_SHARED_LIBS` flag to `ON` when running `cmake`.

Example builds unix default as make, other generators can be specified with the `-G` flag.

```bash
git clone https://github.com/gabmsamu/cpp-sudoku.git
cd cpp-sudoku

mkdir build
cd build

# build static library
cmake ..

# build dynamic library
cmake -BUILD_SHARED_LIBS=ON ..

# Tests are built by default but can be turned off
cmake -BUILD_TESTS=OFF ..

make

```

## install(optional)

```bash

make install

```

## Linking from other projects

### Example in CMake

```cmake

find_package(sudoku REQUIRED)

target_link_libraries(your_target_name PRIVATE cpp-sudoku)

```
