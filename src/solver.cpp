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

bool Solver::update_hashtable(std::shared_ptr<Token> iter, const unsigned int &total_sum) {
    auto var = std::dynamic_pointer_cast<Variable>(iter);
    if (var != nullptr) {
        lhs_var_ht.insert(std::make_pair(var->var_name, total_sum));
        return true;
    }
    return false;
}

bool Solver::update_total_sum_var_tok(std::shared_ptr<Token> token, unsigned int &total_sum) {
    auto var = std::dynamic_pointer_cast<Variable>(token);
    if (var != nullptr) {
        auto it = lhs_var_ht.find(var->var_name);
        if (it != lhs_var_ht.end()) {
            total_sum += it->second;
            return true;
        }
    }
    return false;
}

bool Solver::update_total_sum_int_tok(std::shared_ptr<Token> token, unsigned int &total_sum) {
    auto integer = std::dynamic_pointer_cast<Integer>(token);
    if (integer != nullptr) {
        total_sum += integer->value;
        return true;
    }
    return false;
}

void Solver::update(const std::vector<std::shared_ptr<Token>> &curr_eq, bool &lhs_var_found, unsigned int &lhs_var_not_found_count) {
    equations.push(curr_eq);
    lhs_var_found = false;
    lhs_var_not_found_count++;
}

bool Solver::solve() {
    unsigned int lhs_var_not_found_count = 0;
    unsigned int num_equations = equations.size();

    while (!equations.empty() && lhs_var_not_found_count < num_equations) {
        auto curr_eq = equations.front();
        equations.pop();

        unsigned int total_sum = 0;
        bool lhs_var_found = true;

        for (auto token = curr_eq.rbegin()+1; token != curr_eq.rend(); token++) {
            bool is_interger = update_total_sum_int_tok(*token, total_sum);
            if (is_interger) {
                continue;
            }

            bool is_var = update_total_sum_var_tok(*token, total_sum);
            if (!is_interger && !is_var) {
                return false;
            }
            
            if (!is_var) {
                update(curr_eq, lhs_var_found, lhs_var_not_found_count);
                break;
            }
        }

        if (lhs_var_found) {
            update_hashtable(*curr_eq.rbegin(), total_sum);
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