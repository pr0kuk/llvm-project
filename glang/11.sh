lex l.lex
bison -d grammar.y
cmake ./
make
printf "int i = 0;\nint y[20] = 10;\nint pow(int a){\nreturn a*a;\n}\nint main(){\n  i = 2;\n  for i from 0 to 11 {y[i] = pow(i);\n}\n  y[1] = 1;\nreturn 0;\n}"
printf "int i = 0;\nint y[20] = 10;\nint pow(int a){\nreturn a*a;\n}\nint main(){\n  i = 2;\n  for i from 0 to 11 {y[i] = pow(i);\n}\n  y[1] = 1;\nreturn 0;\n}" | ./pars
