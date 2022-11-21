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

llvm::Function *readFunc;
int readVal() {
    int res = 0;
    std::cin >> res;
    return res; 
}

int main(int argc, char **argv)
{
    llvm::InitializeNativeTarget();
    llvm::InitializeNativeTargetAsmPrinter();

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
    
    readFunc = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "readVal", module);

    yyparse();

    llvm::outs() << "#[LLVM IR]:\n";
    module->print(llvm::outs(), nullptr);

    // Interpreter of LLVM IR
    llvm::outs() << "Running code...\n";
	llvm::ExecutionEngine *ee = llvm::EngineBuilder(std::unique_ptr<llvm::Module>(module)).create();
    ee->InstallLazyFunctionCreator([&](const std::string &fnName) -> void * {
        if (fnName == "readVal") { return reinterpret_cast<void *>(readVal); }
        return nullptr;
    });
    ee->finalizeObject();
	std::vector<llvm::GenericValue> noargs;
	llvm::GenericValue res = ee->runFunction(mainFunc, noargs);
	llvm::outs() << "Code was run. Result = " << res.IntVal << "\n";

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

TERM:    VAL
        | TERM '*' VAL  { $$ = builder->CreateMul($1, $3); }
        | TERM '/' VAL  { $$ = builder->CreateUDiv($1, $3); }
;

VAL:    NUM
        | '?' { $$ = builder->CreateCall(readFunc); }

%%