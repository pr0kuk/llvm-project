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

llvm::LLVMContext context;
llvm::IRBuilder<>* builder;
llvm::Module* module;

typedef struct {
    llvm::GlobalVariable* irVal;
    int realVal;
} value_t;
std::map<std::string, value_t> ValueMap;


typedef struct {
    llvm::GlobalVariable* irVal;
    int size;
    int initVal;
    int* realVal;
} array_t;
std::map<std::string, array_t> ArrayMap;

int main(int argc, char **argv)
{
    llvm::InitializeNativeTarget();
    llvm::InitializeNativeTargetAsmPrinter();

    // ; ModuleID = 'top'
    // source_filename = "top"
    module = new llvm::Module("top", context);
    builder = new llvm::IRBuilder<> (context);

    yyparse();

    llvm::outs() << "#[LLVM IR]:\n";
    module->print(llvm::outs(), nullptr);

    // Interpreter of LLVM IR
    llvm::outs() << "Running code...\n";
	llvm::ExecutionEngine *ee = llvm::EngineBuilder(std::unique_ptr<llvm::Module>(module)).create();

    for (auto& value : ValueMap) {
        ee->addGlobalMapping(value.second.irVal, &value.second.realVal);
    }
    for (auto& array : ArrayMap) {
        array.second.realVal = new int[array.second.size];
        for (int i = 0; i < array.second.size; i++) {
            array.second.realVal[i] = array.second.initVal;
        }
        ee->addGlobalMapping(array.second.irVal, array.second.realVal);
    }

    ee->finalizeObject();
	std::vector<llvm::GenericValue> noargs;
    llvm::Function *mainFunc = module->getFunction("main");
    if (mainFunc == nullptr) {
	    llvm::outs() << "Can't find main\n";
        return -1;
    }
	ee->runFunction(mainFunc, noargs);
	llvm::outs() << "Code was run.\n";

    for (auto& value : ValueMap) {
        llvm::outs() << value.first << " = " <<  value.second.realVal << "\n";
    }
    for (auto& array : ArrayMap) {
        llvm::outs() << array.first << "[" << array.second.size << "] =";
        for (int i = 0; i < array.second.size; i++) {
            llvm::outs() << " " << array.second.realVal[i];
        }
        llvm::outs() << "\n";
        delete array.second.realVal;
    }
    return 0;
}
%}

%token IntLiteral
%token FunctionBegin
%token FunctionEnd
%token Identifier

%%

Parse: Program {YYACCEPT;}

Program: RoutineDeclaration {}
         | VariableDeclaration {} 
         | Program VariableDeclaration {}
         | Program RoutineDeclaration {}

VariableDeclaration : Identifier '=' IntLiteral ';' {
                                                    printf("Identifier '=' IntLiteral ';'\n");
                                                    module->getOrInsertGlobal((char*)$1, builder->getInt32Ty());
                                                    value_t val;
                                                    val.irVal = module->getNamedGlobal((char*)$1);
                                                    val.realVal = atoi((char*)$3);
                                                    ValueMap.insert({(char*)$1, val});
                                                }
                    | Identifier '[' IntLiteral ']''=' IntLiteral ';' {
                                                    printf("Identifier '[' IntLiteral ']''=' IntLiteral ';'\n");
                                                    int size = atoi((char*)$3);
                                                    llvm::ArrayType *arrayType = llvm::ArrayType::get(builder->getInt32Ty(), size);
                                                    module->getOrInsertGlobal((char*)$1, arrayType);
                                                    array_t arr;
                                                    arr.irVal = module->getNamedGlobal((char*)$1);
                                                    arr.size = atoi((char*)$3);
                                                    arr.initVal = atoi((char*)$6);
                                                    ArrayMap.insert({(char*)$1, arr});
                                                }

RoutineDeclaration : FunctionBegin Identifier   {
                                                    printf("FunctionBegin Identifier ...\n");
                                                    // declare void @Identifier()
                                                    llvm::FunctionType *funcType = 
                                                        llvm::FunctionType::get(builder->getVoidTy(), false);
                                                    llvm::Function *func =
                                                        llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, (char*)$2, module);
                                                    // entry:
                                                    llvm::BasicBlock *entryBB = llvm::BasicBlock::Create(context, "entry", func);
                                                    builder->SetInsertPoint(entryBB);
                                                } Statements FunctionEnd { 
                                                    printf("... Statements FunctionEnd\n");
                                                    builder->CreateRetVoid();
                                                }

Statements: Assignment {printf("Assignment\n");}
            | Statements Assignment {printf("Statements Assignment\n");}

Assignment: Value '=' Expression ';' { printf("Value '=' Expression ';'\n"); builder->CreateStore($3, $1); }

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
            | Value { $$ = builder->CreateLoad($1); }
;

Value:      Identifier  {
                            $$ = builder->CreateConstGEP1_32(ValueMap[(char*)$1].irVal, 0);
                        }
            | Identifier '[' Expression ']' {
                            llvm::ArrayType *arrayType = llvm::ArrayType::get(builder->getInt32Ty(), ArrayMap[(char*)$1].size);
                            std::vector<llvm::Value *> gepArgs;
                            gepArgs.push_back(builder->getInt32(0));
                            gepArgs.push_back($3);
                            $$ = builder->CreateGEP(arrayType, ArrayMap[(char*)$1].irVal, gepArgs);
                        }

%%