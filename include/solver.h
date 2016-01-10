#ifndef SOLVER_H
#define SOLVER_H

#include <vector>
#include <unordered_map>
#include <string>
#include <vector>
#include <queue>
#include <memory>

class Token {
  public:
    virtual ~Token() {}
};

class Integer: public Token {
  public:
    unsigned int value;
    Integer(unsigned int val): value(val) {}
};

class Variable: public Token {
  public:
    std::string var_name;
    Variable(const std::string name): var_name(name) {}
};

class Solver {
  private:
    // the equation has the following format:
    // lhs_variable_name -> total_sum -> var1 -> var2
    std::vector<std::shared_ptr<Token>> curr_equation;
    // stores all equations
    std::queue<std::vector<std::shared_ptr<Token>>> equations;
    // all lhs variables which are known are stored in the hashtable as follows:
    // lhs_variable_name, value
    std::unordered_map<std::string, unsigned int> lhs_var_ht;

  public:
    Solver();
    void add_equation(std::string lhs_var_name);
    void add_variable(std::string var_name);
    void add_number(unsigned int value);
    void solve();
    void print_solution();
};

#endif