%{
#include <stdio.h>
int reg = 0;
char op = '+';
int unmin = 0;
%}

%option main
%option yylineno

%%

[/][/].*\n      ; // comment
[1-9][0-9]*           { int opnd = atoi(yytext);
                  if (unmin) opnd =- opnd; unmin=0;
                  switch(op) {
                    case '+': reg += opnd; break;
                    case '-': reg -= opnd; break;
                    case '*': reg *= opnd; break;
                    case '/': reg /= opnd; break;
                  }
                  op = 0;
                }
[-+*/]          { if (op) {
                    if (*yytext=='-')
                      unmin = 1;
                    else {
                      printf("Unexpected operator in line %d\n", yylineno);
                      exit(1);
                    }
                  } else
                    op = *yytext;
                }
[;]             { if (op) {
                    printf("Unexpected semicolon in line %d\n", yylineno);
                    exit(1);
                  }
                  printf("=%d\n", reg);
                  reg = 0;
                  op = '+';
                }
[ \t\r\n]       ; // whitespace
.               { printf("Syntax error in line %d\n", yylineno); exit(1); }
%%
