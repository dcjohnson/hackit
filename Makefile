CC = gcc
CFLAGS = -Wall -std=c99
COMP = $(CC) $(CFLAGS)
LEX = src/lex/

lisp: hackit.o lex.o
	$(COMP) hackit.o lex.o -o hackit

hackit.o: src/hackit.c
	$(COMP) -c src/hackit.c

lex.o: $(LEX)lex.c $(LEX)lex.h
	$(COMP) -c $(LEX)lex.c

clean:
	rm -v *.o
	rm hackit
