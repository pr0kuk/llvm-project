make
build/codegen > build/result.ll
clang build/result.ll -o build/ir_check.out interface.c -lglut -lGL 