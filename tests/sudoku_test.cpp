#include <iostream>
#include <chrono>
#include <fstream>
#include <string>
#include <vector>

#include "../include/sudoku.hpp"

void solve_all(const std::vector<std::string> &grids) {
    Solver solver;
    int solved = 0;
    float total_time = 0.0f;

    for (auto &grid : grids) {
        auto start = std::chrono::high_resolution_clock::now();
        solver.parse_grid(grid);
        bool result = solver.solve();
        auto end = std::chrono::high_resolution_clock::now();
        total_time += std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        if (result) solved++;
    }

    std::cout << "Solved " << solved << " out of " << grids.size() << " puzzles in "
              << total_time << "ms (avg time: " << total_time / grids.size() << "ms)\n";

}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Usage: ./sudoku_test <filename>\n";
        return 1;
    }
    std::ifstream file(argv[1]);
    std::string line;
    std::vector<std::string> grids;
    while (std::getline(file, line)) {
        grids.push_back(line);
    }
    solve_all(grids);
    return 0;
}
