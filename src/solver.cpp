#include "solver.h"
#include <set>

Solver::Solver(): curr_sum(0) {
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

void Solver::increment_total_sum(std::string var_name, unsigned int &total_sum, bool &lhs_var_found) {
    auto it = lhs_var_ht.find(var_name);
    if (it != lhs_var_ht.end()) {
        total_sum += it->second;
    } else {
        lhs_var_found = false;
    }
}

bool Solver::solve() {
    unsigned int lhs_var_not_found_count = 0;
    unsigned int num_equations = equations.size();

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

                increment_total_sum(var->var_name, total_sum, lhs_var_found);
                if (!lhs_var_found) {
                    break;
                }
            } else {
                auto integer = std::dynamic_pointer_cast<Integer>(*token);
                if (integer != nullptr) {
                    total_sum += integer->value;
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
        return true;
    }
    return false;
}

std::vector<std::pair<std::string, unsigned int>> Solver::get_solution() {
    std::set<std::string> res;
    std::vector<std::pair<std::string, unsigned int>> sol;

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