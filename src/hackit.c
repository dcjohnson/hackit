#include "lex/lex.h"
#include "parse/parse.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
	char input[1000];
	token_array toks;
	printf("%s ", ">>");
	fgets(input, 1000, stdin);
	char *err = lex(&toks, input);
	if (err != NULL) {
		puts(err);
		return 0;
	}
	ast new_ast;
	init_ast(&new_ast);
	parse(&toks, &new_ast);

	// for(;;)
	// {
	// 	printf("%s ", ">>");
	// 	fgets(input, 1000, stdin);
	// 	if(feof(stdin))
	// 	{
	// 		break;
	// 	}
	// 	char* err = lex(&toks, input);
	// 	if(err != NULL)
	// 	{
	// 		printf("%s\n", err);
	// 	}
	// 	else
	// 	{
	// 		for(int index = 0; index < toks.len; index++)
	// 		{
	// 			if(toks.tok_array[index].tok_type != LIST)
	// 			{
	// 				printf("%s\n",
	// toks.tok_array[index].tok_data.tok_str);
	// 			}
	// 			else
	// 			{
	// 				printf("%i\n\n",
	// toks.tok_array[index].tok_data.list_len);
	// 			}
	// 		}
	// 	}
	// 	free_tok_array(&toks);
	// }
	return 0;
}
