#include <iostream>

#include "../include/sudoku.hpp"


int count_true(std::array<bool, 9> &arr);

Solver::Solver() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            // row units
            unitlist[i][j] = i * 9 + j;

            // column units
            unitlist[i + 9][j] = j * 9 + i;

            // square units
            unitlist[i + 18][j] = (i / 3 * 3 + j / 3) * 9 + (i % 3 * 3 + j % 3);
        }
    }

    // populate units_of
    // each square belongs to 3 units
    for (int square = 0; square < 81; square++) {
        int unit_count = 0;
        for (int unit = 0; unit < 27; unit++) {
            for (int peer = 0; peer < 9; peer++) {
                if (unitlist[unit][peer] == square) {
                    units_of[square][unit_count] = unit;
                    unit_count++;
                }
            }
        }
    }

    // populate peers
    for (int square = 0; square < 81; square++) {
        int peer_count = 0;
        for (int unit = 0; unit < 3; unit++) {
            for (int peer = 0; peer < 9; peer++) {
                if (unitlist[units_of[square][unit]][peer] != square) {
                    peers[square].insert(unitlist[units_of[square][unit]][peer]);
                }
            }
        }
    }
}

void Solver::parse_grid(std::string_view grid) {
    reset_values();
    int square_idx = 0;
    for (auto &ch : grid) {
        if (ch >= '1' && ch <= '9') {
            if (!assign(square_idx, ch - '0' - 1)) {
                std::cout << "Error: problem parsing board at square: " << square_idx + 1 << "\n";
                std::cout << "Value: " << ch << "\n";
                exit(1);
            }
            square_idx++;
        } else if (ch == '0' || ch == '.') {
            square_idx++;
        }
    }
}

bool Solver::assign(int square_idx, int val_idx) {
    for (int i = 0; i < 9; i++) {
        if (i != val_idx) {
            if (!eliminate(square_idx, i)) return false;
        }
    }
    return true;
}

bool Solver::eliminate(int square_idx, int val_idx) {
    // just for error messages
    int square = square_idx + 1;
    int value = val_idx + 1;


    if (!values[square_idx][val_idx]) return true;

    values[square_idx][val_idx] = false;

    int num_possible_values = count_true(values[square_idx]);

    if (num_possible_values == 0) {
        // std::cout << "Error: Problem eliminating value: " << value << " from square: " << square << "\n";
        // std::cout << "Error: square " << square << " has no possible values\n";
        return false;
    } else if (num_possible_values == 1) {
        int val_idx = 0;
        for (int i = 0; i < 9; i++) {
            if (values[square_idx][i]) {
                val_idx = i;
                break;
            }
        }
        // std::cout << "Assigning square " << square << " to value " << val_idx + 1 << "\n";
        for (auto &peer : peers[square_idx]) {
            if (!eliminate(peer, val_idx)) return false;
        }
    }

    for (auto &unit : units_of[square_idx]) {
        int num_possible_places = 0;
        int possible_place = 0;
        for (auto &peer : unitlist[unit]) {
            if (values[peer][val_idx]) {
                num_possible_places++;
                possible_place = peer;
            }
        }
        if (num_possible_places == 0) {
            // std::cout << "Error: unit " << unit << " has no possible places for value " << value << "\n";
            return false;
        } else if (num_possible_places == 1) {

            if (!assign(possible_place, val_idx)) return false;
        }
    }

    return true;
}

void Solver::display() {

    for (int i = 0; i < 81; i++) {
        if (count_true(values[i]) == 1) {
            for (int j = 0; j < 9; j++) {
                if (values[i][j]) {
                    std::cout << j + 1;
                }
            }
        } else {
            std::cout << ".";
        }
        if (i == 26 || i == 53) {
            std::cout << "\n" << "------+-------+------\n";
        } else if (i % 9 == 2 || i % 9 == 5) {
            std::cout << " | ";
        } else if (i % 9 == 8) {
            std::cout << "\n";
        } else {
            std::cout << " ";
        }
    }
}

bool Solver::solve() {
    int min_num_possible_values = 9;
    int min_square_idx = -1;
    for (int i = 0; i < 81; i++) {
        int num_possible_values = count_true(values[i]);
        if (num_possible_values > 1 && num_possible_values < min_num_possible_values) {
            min_num_possible_values = num_possible_values;
            min_square_idx = i;
        }
    }

    if (min_square_idx == -1) return true;

    for (int i = 0; i < 9; i++) {
        if (values[min_square_idx][i]) {
            Solver copy = *this;
            if (copy.assign(min_square_idx, i)) {
                if (copy.solve()) {
                    *this = copy;
                    return true;
                }
            }
        }
    }
    return false;
}

void Solver::reset_values() {
    for (auto &square : values) {
        for (auto &val : square) {
            val = true;
        }
    }
}

void Solver::display_init() {
    for (auto& unit : unitlist) {;
        for (auto& square : unit) {
            std::cout << square << " ";
        }
        std::cout << "\n";
    }

    for (auto& square : units_of) {
        for (auto& unit : square) {
            std::cout << unit << " ";
        }
        std::cout << "\n";
    }

    for (auto& square : peers) {
        for (auto& peer : square) {
            std::cout << peer << " ";
        }
        std::cout << "\n";
    }
}


int count_true(std::array<bool, 9> &arr) {
    int count = 0;
    for (auto &val : arr) {
        if (val) count++;
    }
    return count;
}
