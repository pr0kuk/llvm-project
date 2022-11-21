%{
#include <iostream>
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/IR/Instructions.h"


#include <vector>
#include <stack>  
#define YYSTYPE llvm::Value*
extern "C" {
    int yyparse();
    int yylex();
    void yyerror(char *s) {
        std::cerr << s << "\n";
    }
    int yywrap(void){return 1;}
}
int whilecounter = 0;

llvm::LLVMContext context;
llvm::IRBuilder<>* builder;
llvm::Module* module;
llvm::Function *curFunc;
std::vector<std::vector<std::pair<llvm::Value*, llvm::Value*>>> peremens;
typedef struct {
    llvm::GlobalVariable* irVal;
    int realVal;
} value_t;
std::map<std::string, value_t> ValueMap;
std::stack<llvm::BasicBlock *> whileCondBB;
std::stack<llvm::BasicBlock *> whileFalseBB;
std::stack<llvm::Value* > forcount;

typedef struct {
    llvm::GlobalVariable* irVal;
    int size;
    int initVal;
    int* realVal;
} array_t;
std::map<std::string, array_t> ArrayMap;
std::stack<int> FuncParams;
std::stack<std::vector<llvm::Value *>> FuncParamsV;
std::map<std::string, llvm::BasicBlock *> BBMap;

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


    //return 0;


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
%token Identifier
%token IfToken
%token WhileToken
%token ForToken
%token From
%token To
%token Type
%token returntoken



%%

Parse: Program {YYACCEPT;}

Program: RoutineDeclaration {}
         | VariableDeclaration {} 
         | Program VariableDeclaration {}
         | Program RoutineDeclaration {}


VariableDeclaration : Type Identifier '=' IntLiteral ';' {
                                                    printf("Type Identifier '=' IntLiteral ';'\n");
                                                    module->getOrInsertGlobal((char*)$2, builder->getInt32Ty());
                                                    value_t val;
                                                    val.irVal = module->getNamedGlobal((char*)$2);
                                                    val.realVal = atoi((char*)$4);
                                                    ValueMap.insert({(char*)$2, val});
                                                }
                    | Type Identifier '[' IntLiteral ']''=' IntLiteral ';' {
                                                    printf("Identifier '[' IntLiteral ']''=' IntLiteral ';'\n");
                                                    int size = atoi((char*)$4);
                                                    llvm::ArrayType *arrayType = llvm::ArrayType::get(builder->getInt32Ty(), size);
                                                    module->getOrInsertGlobal((char*)$2, arrayType);
                                                    array_t arr;
                                                    arr.irVal = module->getNamedGlobal((char*)$2);
                                                    arr.size = atoi((char*)$4);
                                                    arr.initVal = atoi((char*)$7);
                                                    ArrayMap.insert({(char*)$2, arr});
                                                }

Params : %empty {printf("Type Identifier NULL\n"); FuncParams.push(0);}
| Type Identifier {printf("Type Identifier");FuncParams.push(1); FuncParamsV.push({$2});}
    | Params ',' Type Identifier {printf("ParamsDecl, Type Identifier"); int k = FuncParams.top(); FuncParams.pop(); FuncParams.push(k+1); FuncParamsV.top().push_back($4);}

RoutineDeclaration : Type Identifier '('Params')''{' {
                                                    printf("FunctionBegin Identifier ...\n");
                                                    // declare void @Identifier()
                                                    llvm::Function *func = module->getFunction((char*)$2);
                                                    if (func == nullptr) {
                                                        int tt = 0;
                                                        // char* s = (char*)$4;
                                                        // printf("s is %s\n", s);
                                                        // while(s) {
                                                        //     s = strstr(s, "int");
                                                        //     tt++;
                                                        // }
                                                        tt = FuncParams.top();
                                                        std::vector <llvm::Type*> vparams = {};
                                                        for (int ttt = 0; ttt < tt; ttt++)
                                                        {
                                                            vparams.push_back(builder->getInt32Ty());
                                                        }
                                                        printf("tt is %d\n", tt);
                                                        llvm::FunctionType *funcType;
                                                        if (strncmp((char*)$1, "int", 3)) 
                                                            funcType = llvm::FunctionType::get(builder->getInt32Ty(), llvm::ArrayRef<llvm::Type*>(vparams), false);
                                                        else 
                                                            funcType = llvm::FunctionType::get(builder->getVoidTy(), llvm::ArrayRef<llvm::Type*>(vparams), false);

                                                        func = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, (char*)$2, module);
                                                    }
                                                    curFunc = func;
                                                    // entry:
                                                    llvm::BasicBlock *entryBB = llvm::BasicBlock::Create(context, "entry", curFunc);
                                                    builder->SetInsertPoint(entryBB);
                                                    //peremens.push_back()
                                                    std::vector<std::pair<llvm::Value*, llvm::Value*>> pert;
                                                    for (int ti = 0; ti < FuncParams.top(); ti++){
                                                        //FuncParamsV.top()[ti] = builder->CreateAlloca(builder->getInt32Ty());
                                                        //builder->CreateStore(func->getArg(ti), FuncParamsV.top()[ti]);}
                                                        pert.push_back(std::make_pair(FuncParamsV.top()[ti], func->getArg(ti)));
                                                    }
                                                    printf("size PERT is %d\n", pert.size());
                                                    if (pert.size() > 0)
                                                        printf("PERT is %s\n", (char*)pert[0].first);
                                                    peremens.push_back(pert);
                                                    // FuncParams.pop();
                                                    // FuncParamsV.pop();

                                                    printf("fbeg succs \n");
} Statements returntoken Expression ';' '}' { 
                                                    printf("... Statements  Int Function Ret Start\n");
                                                    //printf("ret is %s\n", (char*)$10 );
                                                    //auto&& load = builder->CreateLoad($2); 
                                                    //builder->CreateRet(llvm::ConstantInt::get(builder->getInt32Ty(), 1));

                                                    builder->CreateRet($10);
                                                    printf("... Statements  Int Function Ret End\n");
                                                    }



Statements: %empty
            | Statements Assignment {printf("Statements Assignment\n");}
            | Statements RoutineCall ';' {printf("Statements RoutineCall\n");}
            | Statements IfStatement {printf("Statements IfStatement\n");}
            | Statements While {printf("Statements While\n");}
            | Statements For {printf("Statements For\n");}


Assignment: Value '=' Expression ';' { printf("Value '=' Expression ';'\n"); builder->CreateStore($3, $1); }

RoutineCall: Identifier '(' Expression ')' {
                            printf("routine call started\n");
                            llvm::Function *func = module->getFunction((char*)$1);
                            if (func == nullptr) {
                                llvm::FunctionType *funcType = 
                                                        llvm::FunctionType::get(builder->getInt32Ty(), false);
                                func = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, (char*)$1, module);
                            }
                            $$ = builder->CreateCall(func, $3);
                            printf("routine call finished\n");

                        }

IfStatement: IfToken Expression '|' Identifier '|' Identifier ';' {
                            if (BBMap.find((char*)$4) == BBMap.end()) {
                                BBMap.insert({(char*)$4, llvm::BasicBlock::Create(context, (char*)$4, curFunc)});
                            }
                            if (BBMap.find((char*)$6) == BBMap.end()) {
                                BBMap.insert({(char*)$6, llvm::BasicBlock::Create(context, (char*)$6, curFunc)});
                            }
                            llvm::Value *cond = builder->CreateICmpNE($2, builder->getInt32(0));
                            builder->CreateCondBr(cond, BBMap[(char*)$4], BBMap[(char*)$6]);
                        }

While: WhileToken  {                    
                                        printf("WhileToken start\n");
                                        auto&& condBB = llvm::BasicBlock::Create(context, "", curFunc);
                                        builder->CreateBr(condBB);
                                        builder->SetInsertPoint(condBB);
                                        whileCondBB.push(condBB);
} Expression '{'   {
                                        printf("while expression started\n");
                                        auto && cond = builder->CreateICmpNE($3, builder->getInt32(0));
                                        auto&& falseBB = llvm::BasicBlock::Create(context, "", curFunc);
                                        auto&& trueBB = llvm::BasicBlock::Create(context, "", curFunc);

                                        builder->CreateCondBr(cond, trueBB, falseBB);
                                        builder->SetInsertPoint(trueBB);

                                        whileFalseBB.push(falseBB);
                                        printf("while expression finished\n");

} Statements '}'   {
                                        printf("while statements started\n");
                                        builder->CreateBr(whileCondBB.top());
                                        builder->SetInsertPoint(whileFalseBB.top());
                                        whileCondBB.pop();
                                        whileFalseBB.pop();
                                        printf("WhileToken finish\n");
}


For: ForToken Value From Simple To Simple '{' {                    
                                        printf("ForToken start\n");
                                        builder->CreateStore($4, $2);
                                        auto&& condBB = llvm::BasicBlock::Create(context, "", curFunc);
                                        builder->CreateBr(condBB);
                                        builder->SetInsertPoint(condBB);
                                        whileCondBB.push(condBB);
                                        printf("for expression started\n");
                                        $$ = builder->CreateLoad($2);
                                        auto && cond = builder->CreateICmpSLT($$, $6);
                                        auto&& falseBB = llvm::BasicBlock::Create(context, "", curFunc);
                                        auto&& trueBB = llvm::BasicBlock::Create(context, "", curFunc);
                                        builder->CreateCondBr(cond, trueBB, falseBB);
                                        builder->SetInsertPoint(trueBB);
                                        whileFalseBB.push(falseBB);
                                        forcount.push($2);
                                        printf("for expression finished\n");
} Statements '}' {
                                        printf("for statements started\n");
                                        $$ = builder ->CreateLoad(forcount.top());
                                        $$ = builder->CreateAdd($$, llvm::ConstantInt::get(builder->getInt32Ty(), 1));
                                        builder->CreateStore($$, forcount.top());
                                        builder->CreateBr(whileCondBB.top());
                                        builder->SetInsertPoint(whileFalseBB.top());
                                        whileCondBB.pop();
                                        whileFalseBB.pop();
                                        forcount.pop();
                                        printf("for statements finish\n");
}


Expression: Simple
            | Expression '!''=' Simple { $$ = builder->CreateZExt(builder->CreateICmpNE($1, $4), builder->getInt32Ty()); }
            | Expression '=''=' Simple { $$ = builder->CreateZExt(builder->CreateICmpEQ($1, $4), builder->getInt32Ty()); }
            | Expression '<'    Simple { $$ = builder->CreateZExt(builder->CreateICmpSLT($1, $3), builder->getInt32Ty()); }
            | Expression '<''=' Simple { $$ = builder->CreateZExt(builder->CreateICmpSLE($1, $4), builder->getInt32Ty()); }
            | Expression '>'    Simple { $$ = builder->CreateZExt(builder->CreateICmpSGT($1, $3), builder->getInt32Ty()); }
            | Expression '>''=' Simple { $$ = builder->CreateZExt(builder->CreateICmpSGE($1, $4), builder->getInt32Ty()); }
            | RoutineCall
            | %empty
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
                            if (ValueMap.find((char*)$1) != ValueMap.end()) {
                                $$ = builder->CreateConstGEP1_32(ValueMap[(char*)$1].irVal, 0);
                            }
                            else {
                                printf("searching %s in local peremens\n", (char*)$1);
                                for (auto ii:peremens.back()) {
                                    printf("i1.first is %s\n", (char*)ii.first);
                                   // printf("i1.second is %d\n", (int)ii.second);

                                    if (strcmp((char*)$1, (char*)ii.first), 1) {printf("FOUND\n"); $$ = builder->CreateAlloca(builder->getInt32Ty()); builder->CreateStore(ii.second, $$); }}
                                //$$ = *(peremens.end())
                            }
                        }
            | Identifier '[' Expression ']' {
                            llvm::ArrayType *arrayType = llvm::ArrayType::get(builder->getInt32Ty(), ArrayMap[(char*)$1].size);
                            std::vector<llvm::Value *> gepArgs;
                            gepArgs.push_back(builder->getInt32(0));
                            gepArgs.push_back($3);
                            $$ = builder->CreateGEP(arrayType, ArrayMap[(char*)$1].irVal, gepArgs);
                        }

%%