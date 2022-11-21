lex 6.lex
bison -d 6.y
g++ lex.yy.c 6.tab.c `llvm-config --cppflags --ldflags --libs` -o lex6
echo "x + 10*y - (0 == -x) != 0;"
echo "x + 10*y - (0 == -x) != 0;" | ./lex6