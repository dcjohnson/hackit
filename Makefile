CC = gcc
CFLAGS = -Wall -std=c99
COMP = $(CC) $(CFLAGS)

lisp: hackit.o lex.o
	$(COMP) hackit.o lex.o -o hackit

hackit.o: src/hackit.c
	$(COMP) -c src/hackit.c

lex.o: src/lex/lex.c src/lex/lex.h
	$(COMP) -c src/lex/lex.c

clean:
	rm -v *.o
	rm hackit
