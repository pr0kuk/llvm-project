%{
#define YYSTYPE void*
#include "grammar.tab.h"
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
"return"        {printf("returntoken\n");return returntoken;}
"if"            { printf("IfToken\n"); return IfToken; }
"while"         { printf("WhileToken\n"); return WhileToken; }
"for"           { printf("ForToken\n"); return ForToken; }
"int"           { printf("type int\n"); return Type;}
"void"          { printf("type void\n"); return Type;}
"from"          { printf("lit from\n"); return From;}
"to"            { printf("lit to\n"); return To;}
"gl_init"     {  printf("gl_init\n"); return GlInit;}
"gl_put_pixel"     { printf("gl_putpixel\n"); return GlPutPixel;}
"print"             { printf("print\n"); return print;}



[A-Za-z_]+      { // identifier or array
                  printf("Identifier %s\n", yytext);
                  yylval = strdup(yytext);
                  return Identifier;
                }
[ \t\r\n]      ; // whitespace
.              { return *yytext; }

%%
