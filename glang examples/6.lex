%{
#include "llvm/IR/IRBuilder.h"

#define YYSTYPE llvm::Value*
#include "6.tab.h"
extern "C" int yylex();
extern llvm::IRBuilder<>* builder;
extern std::map<std::string, llvm::GlobalVariable*> IdentifierMap;
extern llvm::Module* module;
%}

%option yylineno
%option noyywrap

%%

[/][/].*\n      ; // comment
[0-9]+          {
                  yylval = builder->getInt32(atoi(yytext));
                  return IntLiteral;
                }
[A-Za-z_]+      { // identifier
                  // printf("Identifier: %s\n", yytext);
                  if (IdentifierMap.find(yytext) == IdentifierMap.end()) {
                    module->getOrInsertGlobal(yytext, builder->getInt32Ty());
                    IdentifierMap.insert({yytext, module->getNamedGlobal(yytext)});
                  }
                  yylval = builder->CreateConstGEP1_32(IdentifierMap[yytext], 0);
                  return Identifier;
                }
[ \t\r\n]      ; // whitespace
.              { return *yytext; }

%%