%{
#include <iostream>
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/Support/TargetSelect.h"

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
llvm::Module* module;

std::map<std::string, llvm::GlobalVariable*> ValueMap;
std::map<std::string, llvm::GlobalVariable*> ArrayMap;

int main(int argc, char **argv)
{
    llvm::InitializeNativeTarget();
    llvm::InitializeNativeTargetAsmPrinter();

    llvm::LLVMContext context;
    // ; ModuleID = 'top'
    // source_filename = "top"
    module = new llvm::Module("top", context);
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

    // Interpreter of LLVM IR
    llvm::outs() << "Running code...\n";
	llvm::ExecutionEngine *ee = llvm::EngineBuilder(std::unique_ptr<llvm::Module>(module)).create();
    for (auto& value : ValueMap) {
        ee->addGlobalMapping(value.second, new int(0));
    }
    for (auto& array : ArrayMap) {
        ee->addGlobalMapping(array.second, new int[100]);
    }
    ee->finalizeObject();
	std::vector<llvm::GenericValue> noargs;
	llvm::GenericValue res = ee->runFunction(mainFunc, noargs);
	llvm::outs() << "Code was run. Result = " << res.IntVal << "\n";
    return 0;
}
%}

%token IntLiteral
%token Identifier

%%

Program:    Expression ';' { builder->CreateRet($$); YYACCEPT; };

Expression: Simple
            | Expression '!''=' Simple { $$ = builder->CreateZExt(builder->CreateICmpNE($1, $4), builder->getInt32Ty()); }
            | Expression '=''=' Simple { $$ = builder->CreateZExt(builder->CreateICmpEQ($1, $4), builder->getInt32Ty()); }
            | Expression '<'    Simple { $$ = builder->CreateZExt(builder->CreateICmpSLT($1, $3), builder->getInt32Ty()); }
            | Expression '<''=' Simple { $$ = builder->CreateZExt(builder->CreateICmpSLE($1, $4), builder->getInt32Ty()); }
            | Expression '>'    Simple { $$ = builder->CreateZExt(builder->CreateICmpSGT($1, $3), builder->getInt32Ty()); }
            | Expression '>''=' Simple { $$ = builder->CreateZExt(builder->CreateICmpSGE($1, $4), builder->getInt32Ty()); }
;
Simple:     Summand
            | Simple '+' Summand { $$ = builder->CreateAdd($1, $3); }
            | Simple '-' Summand { $$ = builder->CreateSub($1, $3); }

Summand:    Factor
            | Summand '*' Factor  { $$ = builder->CreateMul($1, $3); }
            | Summand '/' Factor  { $$ = builder->CreateSDiv($1, $3); }
            | Summand '%' Factor  { $$ = builder->CreateSRem($1, $3); }
;

Factor:     Primary { $$ = $1; }
            | '-' Primary { $$ = builder->CreateNeg($2); }
            | '(' Expression ')' { $$ =$2; }
;

Primary:    IntLiteral { $$ = builder->getInt32(atoi((char*)$1)); }
            | Value { $$ = $1; }
;

Value:      Identifier  {
                          if (ValueMap.find((char*)$1) == ValueMap.end()) {
                            module->getOrInsertGlobal((char*)$1, builder->getInt32Ty());
                            ValueMap.insert({(char*)$1, module->getNamedGlobal((char*)$1)});
                          }
                          $$ = builder->CreateLoad(builder->CreateConstGEP1_32(ValueMap[(char*)$1], 0));
                        }
            | Identifier '[' Expression ']' {
                          llvm::ArrayType *arrayType = llvm::ArrayType::get(builder->getInt32Ty(), 100);
                          if (ArrayMap.find((char*)$1) == ArrayMap.end()) {
                            module->getOrInsertGlobal((char*)$1, arrayType);
                            ArrayMap.insert({(char*)$1, module->getNamedGlobal((char*)$1)});
                          }
                          std::vector<llvm::Value *> gepArgs;
                          gepArgs.push_back(builder->getInt32(0));
                          gepArgs.push_back($3);
                          $$ = builder->CreateLoad(builder->CreateGEP(arrayType, ArrayMap[(char*)$1], gepArgs));
                        }

%%