make
build/codegen > result.ll
clang result.ll -o kek interface.c -lglut -lGL