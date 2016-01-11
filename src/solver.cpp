#include "solver.h"
#include <iostream>
#include <set>

Solver::Solver(): curr_sum(0), is_solvable(false) {
}

void Solver::add_equation(std::string lhs_var_name) {
    if (curr_equation.empty()) {
        lhs_var_ht.insert(std::make_pair(lhs_var_name, curr_sum));
    } else {
        curr_equation.push_back(std::make_shared<Integer>(curr_sum));
        curr_equation.push_back(std::make_shared<Variable>(lhs_var_name));
        equations.push(curr_equation);
    }

    curr_equation.clear();
    curr_sum = 0;
}

void Solver::add_variable(std::string var_name) {
    curr_equation.push_back(std::make_shared<Variable>(var_name));
}

void Solver::add_number(unsigned int value) {
    curr_sum += value;
}

void Solver::solve() {
    unsigned int lhs_var_not_found_count = 0;
    unsigned int num_equations = equations.size();
    is_solvable = false;

    while (!equations.empty() && lhs_var_not_found_count < num_equations) {
        auto curr_eq = equations.front();
        equations.pop();

        unsigned int total_sum = 0;
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
                    total_sum += it->second;
                } else {
                    lhs_var_found = false;
                    break;
                }
            } else {
                auto box = std::dynamic_pointer_cast<Integer>(*token);
                if (box != nullptr) {
                    total_sum += box->value;
                }
            }
        }

        if (!lhs_var_found) {
            equations.push(curr_eq);
            lhs_var_not_found_count++;
        } else {
            lhs_var_ht.insert(std::make_pair(lhs_var_name, total_sum));
        }
    }

    if (equations.empty()) {
        is_solvable = true;
    }
}

std::vector<std::pair<std::string, unsigned int>> Solver::get_solution() {
    std::set<std::string> res;
    std::vector<std::pair<std::string, unsigned int>> sol;

    if (!is_solvable) {
        std::cout << "Error: Equation System is not solvable" << std::endl;
        return sol;
    }

    for (auto &e: lhs_var_ht) {
        res.insert(e.first);
    }

    for (auto &e: res) {
        auto it = lhs_var_ht.find(e);
        if (it != lhs_var_ht.end()) {
            sol.push_back(std::make_pair(it->first, it->second));
        }
    }

    return sol;
}