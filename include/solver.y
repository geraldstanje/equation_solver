%{
#include <cstdio>
#include <string>
#include "solver.h"

extern void yyerror(const char *msg);
extern int yylex(void);
extern int yyparse(void);

Solver solver;
%}

%union {
  char *str;
  unsigned int ival; /* NUMBER */
}

%token <ival> NUMBER
%token <str> VARNAME
%left PLUS
%token EQUAL
%token END

%start Input

%%

Input
  : /* Empty */
  | Line { }
  ;

Line
  : Line END { }
  | VARNAME EQUAL Expression END { solver.add_equation(std::string($1)); }
  | Line VARNAME EQUAL Expression END { solver.add_equation(std::string($2)); }
  | Line VARNAME EQUAL Expression { solver.add_equation(std::string($2)); }
  ;

Expression
  : Expression PLUS Expression {}
  | NUMBER { solver.add_number($1); }
  | VARNAME { solver.add_variable(std::string($1)); }
  ;

%%