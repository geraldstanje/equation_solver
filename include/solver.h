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
  // var_name_lhs -> total_sum -> var1 -> var2
  std::vector<std::shared_ptr<Token>> curr_equation;
  // stores all equations
  std::queue<std::vector<std::shared_ptr<Token>>> equation;
  // all lhs variables which are known are stored in the hashtable as follows:
  // variable_lhs, unsigned integer value
  std::unordered_map<std::string, unsigned int> variable_ht;

public:
  Solver();
  void add_equation(std::string var_name_lhs);
  void add_variable(std::string var_name);
  void add_number(unsigned int value);
  void solve();
  void print_solution();
};

#endif