#include <vector>
#include <array>
#include <string_view>
#include <set>


class Solver {

public:
    Solver();

    // parses a Sudoku board given as text, and populates the values array
    // The textual representation is a string of 81 characters, where 0 or . represents an empty square
    // and 1-9 represents a filled square, all other tokens will be ignored
    void parse_grid(std::string_view grid);

    // Assigns a value to a square, and eliminating all other potential values from the square
    // and propagating the constraints to the other squares
    bool assign(int square, int value);

    // Eliminates a value from a square, and propagating the constraints to the other squares
    bool eliminate(int square, int value);
    // Displays board as a 2d grid
    void display();

    // attempts to solve the board that is currently loaded into the values array
    bool solve();

    void display_init();

private:
    // array of all units that exist on the board
    // 27 units, 9 squares per unit
    std::array<std::array<int, 9>, 27> unitlist;

    // maps each square index to an array of the units that it belongs to
    std::array<std::array<int, 3>, 81> units_of;

    // maps each square index to an array of the unique squares that it shares a unit with
    // 20 peers per square
    std::array<std::set<int>, 81> peers;

    // maps each square index to an array of the possible values that it can take
    std::array<std::array<bool, 9>, 81> values;

    void reset_values();
};
