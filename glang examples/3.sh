lex 3.lex
bison -d 3.y
g++ -ly lex.yy.c 3.tab.c -o lex3
echo "22+ 3*4 -5;"
echo "22+ 3*4 -5;" | ./lex3