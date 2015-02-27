CC = clang
CFLAGS = -Wall -O0 -g -std=c99
COMP = $(CC) $(CFLAGS)

hackit: hackit.o lex.o parse.o
	$(COMP) hackit.o lex.o parse.o -o hackit

hackit.o: src/hackit.c
	$(COMP) -c src/hackit.c

lex.o: src/lex/lex.c src/lex/lex.h
	$(COMP) -c src/lex/lex.c

parse.o: src/parse/parse.c src/parse/parse.h
	$(COMP) -c src/parse/parse.c

clean:
	rm -v *.o
	rm hackit
