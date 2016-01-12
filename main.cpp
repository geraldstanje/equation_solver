#include "solver.h"
#include "y.tab.hpp"
#include <iostream>
#include <fstream>

int yyparse();
int yylex();
extern FILE *yyin;
extern Solver solver;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s filename\n", argv[0]);
        exit(1);
    }

    yyin = fopen(argv[1], "r+");
    yyparse();
    fclose(yyin);

    bool can_solve = solver.solve();
    if (!can_solve) {
        std::cerr << "Error: Equation System is not solvable" << std::endl;
        return 0;
    }
    auto sol = solver.get_solution();
    for (auto &e: sol) {
        std::cout << e.first << ": " << e.second << std::endl;
    }

    return 0;
}