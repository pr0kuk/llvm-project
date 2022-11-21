lex 4.lex
bison -d 4.y
g++ lex.yy.c 4.tab.c `llvm-config --cppflags --ldflags --libs` -o lex4
echo "22+ 3*4 -5;"
echo "22+ 3*4 -5;" | ./lex4