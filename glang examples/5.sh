lex 5.lex
bison -d 5.y
g++ lex.yy.c 5.tab.c `llvm-config --cppflags --ldflags --libs` -o lex5
echo "22+ 3*5*? -5;"
./lex5