%{
#include <iostream>
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"

#define YYSTYPE llvm::Value*
extern "C" {
    int yyparse();
    int yylex();
    void yyerror(char *s) {
        std::cerr << s << "\n";
    }
    int yywrap(void){return 1;}
}
llvm::IRBuilder<>* builder;

int main(int argc, char **argv)
{
    llvm::LLVMContext context;
    // ; ModuleID = 'top'
    // source_filename = "top"
    llvm::Module* module = new llvm::Module("top", context);
    builder = new llvm::IRBuilder<> (context);

    // declare void @main()
    llvm::FunctionType *funcType = 
        llvm::FunctionType::get(builder->getInt32Ty(), false);
    llvm::Function *mainFunc =
        llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "main", module);
    // entry:
    llvm::BasicBlock *entryBB = llvm::BasicBlock::Create(context, "entry", mainFunc);
    builder->SetInsertPoint(entryBB);

    yyparse();

    llvm::outs() << "#[LLVM IR]:\n";
    module->print(llvm::outs(), nullptr);
    return 0;
}
%}

%token NUM

%%

EVALUATE: EXPR ';' { builder->CreateRet($$); YYACCEPT; };

EXPR:    TERM
        | EXPR '+' TERM { $$ = builder->CreateAdd($1, $3); }
        | EXPR '-' TERM { $$ = builder->CreateSub($1, $3); }
;

TERM:    NUM
        | TERM '*' NUM  { $$ = builder->CreateMul($1, $3); }
        | TERM '/' NUM  { $$ = builder->CreateUDiv($1, $3); }
;

%%