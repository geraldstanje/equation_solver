#include "solver.h"
#include <iostream>
#include <set>

Solver::Solver() {
}

void Solver::add_equation(std::string lhs_var_name) {
    if (curr_equation.size() == 1) {
        auto box = std::dynamic_pointer_cast<Integer>(curr_equation.front());
        if (box != nullptr) {
            lhs_var_ht.insert(std::make_pair(lhs_var_name, box->value));
        }
    } else if (curr_equation.size() > 1) {
        curr_equation.insert(curr_equation.begin(), std::make_shared<Variable>(lhs_var_name));
        equations.push(curr_equation);
    }

    curr_equation.clear();
}

void Solver::add_variable(std::string var_name) {
    curr_equation.push_back(std::make_shared<Variable>(var_name));
}

void Solver::add_number(unsigned int value) {
    if (curr_equation.size() > 0) {
        auto box = std::dynamic_pointer_cast<Integer>(curr_equation.front());
        if (box != nullptr) {
            box->value += value;
        } else {
            curr_equation.insert(curr_equation.begin(), std::make_shared<Integer>(value));
        }
    } else {
        curr_equation.insert(curr_equation.begin(), std::make_shared<Integer>(value));
    }
}

void Solver::solve() {
    while (!equations.empty()) {
        auto curr_eq = equations.front();
        equations.pop();

        unsigned int curr_sum = 0;
        bool var_found = true;
        std::string var_name_lhs;

        for (auto token = curr_eq.begin(); token != curr_eq.end(); token++) {
            auto var = std::dynamic_pointer_cast<Variable>(*token);
            if (var != nullptr) {
                if (token == curr_eq.begin()) {
                    var_name_lhs = var->var_name;
                    continue;
                }

                auto it = lhs_var_ht.find(var->var_name);
                if (it != lhs_var_ht.end()) {
                    curr_sum += it->second;
                } else {
                    var_found = false;
                    break;
                }
            } else {
                auto box = std::dynamic_pointer_cast<Integer>(*token);
                if (box != nullptr) {
                    curr_sum += box->value;
                }
            }
        }

        if (!var_found) {
            equations.push(curr_eq);
        } else {
            lhs_var_ht.insert(std::make_pair(var_name_lhs, curr_sum));
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