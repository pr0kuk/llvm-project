lex 8.lex
bison -d 8.y
g++ lex.yy.c 8.tab.c `llvm-config --cppflags --ldflags --libs` -o lex8
printf "x = 3;\ny[20] = 10;\n\nfunc main\n  y[2 + x] = -7;\n  x = x + 3;\n  y[2*x] = 3;\nend\n"
printf "x = 3;\ny[20] = 10;\n\nfunc main\n  y[2 + x] = -7;\n  x = x + 3;\n  y[2*x] = 3;\nend\n" | ./lex8