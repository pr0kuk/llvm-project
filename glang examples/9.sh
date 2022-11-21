lex 9.lex
bison -d 9.y
g++ lex.yy.c 9.tab.c `llvm-config --cppflags --ldflags --libs` -o lex9
printf "i = 0;\ny[20] = 10;\n\nfunc main\n  i = 2;\n  y[0] = 0;\n  y[1] = 1;\nloop:\n  if i < 20 | iteration | loop_end;\niteration:\n  call fib;\n  i = i + 1;\n  goto loop;\nloop_end:\n  i = y[10];\nend\n\nfunc fib\n  y[i] = y[i-1] + y[i-2];\nend\n"
printf "i = 0;\ny[20] = 10;\n\nfunc main\n  i = 2;\n  y[0] = 0;\n  y[1] = 1;\nloop:\n  if i < 20 | iteration | loop_end;\niteration:\n  call fib;\n  i = i + 1;\n  goto loop;\nloop_end:\n  i = y[10];\nend\n\nfunc fib\n  y[i] = y[i-1] + y[i-2];\nend\n" | ./lex9