lex l.lex
bison -d grammar.y
cmake ./
make