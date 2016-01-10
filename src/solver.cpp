#include "solver.h"
#include <iostream>
#include <set>

Solver::Solver(): total_sum(0) {
}

void Solver::add_equation(std::string lhs_var_name) {
    curr_equation.push_back(std::make_shared<Integer>(total_sum));
    curr_equation.push_back(std::make_shared<Variable>(lhs_var_name));
    equations.push(curr_equation);

    curr_equation.clear();
    total_sum = 0;
}

void Solver::add_variable(std::string var_name) {
    curr_equation.push_back(std::make_shared<Variable>(var_name));
}

void Solver::add_number(unsigned int value) {
    total_sum += value;
}

void Solver::solve() {
    while (!equations.empty()) {
        auto curr_eq = equations.front();
        equations.pop();

        unsigned int curr_sum = 0;
        bool lhs_var_found = true;
        std::string lhs_var_name;

        for (auto token = curr_eq.rbegin(); token != curr_eq.rend(); token++) {
            auto var = std::dynamic_pointer_cast<Variable>(*token);
            if (var != nullptr) {
                if (token == curr_eq.rbegin()) {
                    lhs_var_name = var->var_name;
                    continue;
                }

                auto it = lhs_var_ht.find(var->var_name);
                if (it != lhs_var_ht.end()) {
                    curr_sum += it->second;
                } else {
                    lhs_var_found = false;
                    break;
                }
            } else {
                auto box = std::dynamic_pointer_cast<Integer>(*token);
                if (box != nullptr) {
                    curr_sum += box->value;
                }
            }
        }

        if (!lhs_var_found) {
            equations.push(curr_eq);
        } else {
            lhs_var_ht.insert(std::make_pair(lhs_var_name, curr_sum));
        }
    }
}

void Solver::print_solution() {
    std::set<std::string> res;

    for (auto &e: lhs_var_ht) {
        res.insert(e.first);
    }

    for (auto &e: res) {
        auto it = lhs_var_ht.find(e);
        if (it != lhs_var_ht.end()) {
            std::cout << it->first << ": " << it->second << std::endl;
        }
    }
}