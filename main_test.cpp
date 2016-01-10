#include "solver.h"
#include "y.tab.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>

int yyparse();
int yylex();
extern FILE *yyin;
extern Solver solver;

int main(int argc, char *argv[]) {
    yyin = fopen("test/equations1.txt", "r+");
    yyparse();
    fclose(yyin);

    solver.solve();

    std::vector<std::pair<std::string, unsigned int>> expected_solution = {{"location", 16},
        {"offset", 7},
        {"origin", 8},
        {"random", 2}
    };
    auto sol = solver.get_solution();
    for (unsigned i = 0; i < sol.size(); i++) {
        assert(sol[i].first == expected_solution[i].first);
        assert(sol[i].second == expected_solution[i].second);
    }

    return 0;
}