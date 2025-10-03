main: main.c lex.yy.c parse.tab.c
	gcc -Wall -Wextra -o main main.c
lex.yy.c: lex.l
	flex lex.l
parse.tab.c: parse.y
	bison parse.y