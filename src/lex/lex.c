#include "lex.h"

tok_struct lex_str(char* str)
{
	tok_struct tokens;
	tokens.tok_array = NULL;
	tokens.tok_len = 0;
	unsigned int index = 0;

	while(str[index] != '\0')
	{
		if(str[index] == '(')
		{
			inc_tok_struct(&tokens);

		}
	}

	return tokens;
}

void inc_tok_struct(tok_struct* tokens)
{
	tokens->tok_len++;
	tokens->tok_array = realloc(tokens->tok_array, sizeof(char*) * tokens->tok_len);
}

void add_to_tok_struct(tok_struct* tokens, char* new_str, unsigned int new_str_len)
{
	inc_tok_struct(tokens);
	tokens->tok_array[tokens->tok_len - 1] = malloc(sizeof(char) * (new_str_len + 1));
	memcpy(tokens->tok_array[tokens->tok_len - 1], new_str, new_str_len);
	tokens->tok_array[tokens->tok_len - 1][new_str_len + 1] = '\0';
}
