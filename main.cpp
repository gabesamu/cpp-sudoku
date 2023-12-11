#include "include/sudoku.hpp"


int main() {
    Solver solver;
    // solver.display_init();
    // solver.parse_grid("003020600900305001001806400008102900700000008006708200002609500800203009005010300");
    // solver.display();

    solver.parse_grid("4.....8.5.3..........7......2.....6.....8.4......1.......6.3.7.5..2.....1.4......");
    // solver.display();
    solver.solve();
    solver.display();
    return 0;
}
