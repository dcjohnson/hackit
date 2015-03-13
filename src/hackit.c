#include "lex/lex.h"
#include "parse/parse.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
	char input[1000];
	token_array toks;
	ast new_ast;
	init_ast(&new_ast);

	for(;;)
	{
		printf("%s ", ">>");
		fgets(input, 1000, stdin);
		if(feof(stdin))
		{
			break;
		}
		lex(&toks, input);
		parse(&toks, &new_ast);
		free_tok_array(&toks);
	}
	return 0;
}
