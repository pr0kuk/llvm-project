%{
#define YYSTYPE void*
#include "9.tab.h"
extern "C" int yylex();
%}

%option yylineno
%option noyywrap

%%

[/][/].*\n      ; // comment
[0-9]*          {
                  printf("IntLiteral %s\n", yytext);
                  yylval = strdup(yytext);
                  return IntLiteral;
                }
[f][u][n][c]    { printf("FunctionBegin\n"); return FunctionBegin; }
[e][n][d]       { printf("FunctionEnd\n"); return FunctionEnd; }
[c][a][l][l]    { printf("CallFunction\n"); return CallFunction; }
[i][f]          { printf("IfToken\n"); return IfToken; }
[g][o][t][o]    { printf("GotoToken\n"); return GotoToken; }
[A-Za-z_]+      { // identifier or array
                  printf("Identifier %s\n", yytext);
                  yylval = strdup(yytext);
                  return Identifier;
                }
[ \t\r\n]      ; // whitespace
.              { return *yytext; }

%%