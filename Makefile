CC = clang
CFLAGS = -Wall -O0 -g -std=c99
COMP = $(CC) $(CFLAGS)
OBJFILES = hackit.o lex.o parse.o ast.o builtins.o eval.o

hackit: $(OBJFILES)
	$(COMP) $(OBJFILES) -o hackit

hackit.o: src/hackit.c
	$(COMP) -c src/hackit.c

lex.o: src/lex/lex.c src/lex/lex.h
	$(COMP) -c src/lex/lex.c

parse.o: src/parse/parse.c src/parse/parse.h
	$(COMP) -c src/parse/parse.c

ast.o: src/ast/ast.c src/ast/ast.h
	$(COMP) -c src/ast/ast.c

builtins.o: src/builtins/builtins.c src/builtins/builtins.h
	$(COMP) -c src/builtins/builtins.c

eval.o: src/eval/eval.c src/eval/eval.h
	$(COMP) -c src/eval/eval.c

clean:
	rm -v $(OBJFILES) hackit
