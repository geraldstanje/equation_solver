#ifndef SOLVER_H
#define SOLVER_H

#include <vector>
#include <unordered_map>
#include <string>
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
    unsigned int curr_sum;
    // the equation will be stored in the following format:
    // var1 -> var2 -> varx -> total_sum -> lhs_variable_name
    std::vector<std::shared_ptr<Token>> curr_equation;
    // stores all equations
    std::queue<std::vector<std::shared_ptr<Token>>> equations;
    // all lhs variables which are known are stored in the hashtable as follows:
    // lhs_variable_name, total_sum
    std::unordered_map<std::string, unsigned int> lhs_var_ht;

  private:
    void update(const std::vector<std::shared_ptr<Token>> &curr_eq, bool &lhs_var_found, unsigned int &lhs_var_not_found_count);
    bool update_hashtable(std::shared_ptr<Token> iter, const unsigned int &total_sum);
    bool update_total_sum_int_tok(std::shared_ptr<Token> token, unsigned int &total_sum);
    bool update_total_sum_var_tok(std::shared_ptr<Token> token, unsigned int &total_sum);

  public:
    Solver();
    void add_equation(std::string lhs_var_name);
    void add_variable(std::string var_name);
    void add_number(unsigned int value);
    bool solve();
    std::vector<std::pair<std::string, unsigned int>> get_solution();
};

#endif