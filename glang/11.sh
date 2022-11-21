lex l.lex
bison -d grammar.y
cmake ./
make
printf "int i = 0;\nint y[20] = 10;int main(){\n  i = 2;\n  y[0] = 0;\n  y[1] = 1;\nreturn 15;\n}\n\n"
printf "int i = 0;\nint y[20] = 10;int main(int a){\n  i = 2;\n  y[0] = 0;\n  y[1] = 1;\nreturn 15;\n}\n\n" | ./pars
