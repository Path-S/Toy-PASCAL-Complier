# Makefile for TOY-PSACAL-COMPLIER
clean:
	rm -rf *.o
	rm lex.yy.c
	rm y.tab.c

# To compile your file lexan.l --> lexer

lexer:  lex.yy.o mainlex.o printtoken.o token.h lexcial.h
	cc -o lexer lex.yy.o mainlex.o printtoken.o

mainlex.o: mainlex.c token.h lexcial.h
	cc -c mainlex.c

lex.yy.o: lex.yy.c
	cc -c lex.yy.c

lex.yy.c: lexcial.l token.h
	lex lexcial.l

printtoken.o: printtoken.c token.h
	cc -c printtoken.c


# To compile your file parse.y --> parser
#      using your file lexan.l
parser: mainparser.o parsetools.o y.tab.o lex.yy.o printtoken.o pprint.o symtab.o geninter.o
	cc -o parser mainparser.o parsetools.o y.tab.o lex.yy.o printtoken.o pprint.o symtab.o geninter.o -ll

mainparser.o: mainparser.c token.h parse.h symtab.h lexcial.h pprint.h
	cc -c mainparser.c

parsefun.o: parsetools.c token.h parse.h symtab.h lexcial.h pprint.h
	cc -c parsetools.c

y.tab.o: y.tab.c
	cc -c y.tab.c

y.tab.c: parse.y token.h parse.h symtab.h lexcial.h
	yacc parse.y

pprint.o: pprint.c token.h pprint.h
	cc -c pprint.c

symtab.o: symtab.c token.h symtab.h
	cc -c symtab.c

geninter.o: geninter.c token.h geninter.h 
	cc -c geninter.c