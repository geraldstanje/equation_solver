%{
#include "y.tab.hpp"
#include <cstdlib>

void yyerror(const char *msg);
%}

/* Add this to get line numbers... */
%option yylineno

number      [0-9]+
whitespace  [ \t]+
var         [A-Za-z][A-Za-z0-9_]*

%%

{number}      { yylval.ival = atof (yytext); return NUMBER; }
"+"           { return PLUS; }
"="           { return EQUAL; }
{whitespace}  { ; }
\n            { return END; }
{var}         { yylval.str = strdup (yytext); return VARNAME; }

%%

void yyerror(const char *msg) {
  fprintf(stderr, "ERROR: %s at symbol '%s' on line %d\n", msg, yytext, yylineno);
  exit(1);
}

int yywrap (void) {
  return 1;
}