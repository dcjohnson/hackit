#include "lex.h"

token_array lex(char* str)
{
	token_array tokens;
	tokens.tok_array = NULL;
	tokens.len = 0;
	unsigned int index = 0;

	while(str[index] != '\0')
	{
		if(str[index] == '"')
		{
			tokens = lex_str(tokens, &str[index]);
		}
		else if(str[index] == '(')
		{
			tokens = add_to_tok_array(tokens, &str[index], 1, OPAREN);
		}
		else if(str[index] == ')')
		{
			tokens = add_to_tok_array(tokens, &str[index], 1, CPAREN);
		}
	}

	return tokens;
}

token_array inc_tok_array(token_array tokens)
{
	tokens.len++;
	tokens.tok_array = realloc(tokens.tok_array, sizeof(token) * tokens.len);
	tokens.tok_array[tokens.len - 1].tok_str = NULL;
	return tokens;
}

token_array add_to_tok_array(token_array tokens, char* new_str, unsigned int new_str_len, type tok_type)
{
	tokens = inc_tok_array(tokens);
	tokens.tok_array[tokens.len - 1].tok_str = malloc(sizeof(char) * (new_str_len + 1));
	memcpy(tokens.tok_array[tokens.len - 1].tok_str, new_str, new_str_len);
	tokens.tok_array[tokens.len - 1].tok_str[new_str_len] = '\0';
	tokens.tok_array[tokens.len - 1].tok_type = tok_type;
	return tokens;
}

token_array lex_str(token_array tokens, char* unlexed_str)
{
	return tokens;
}
