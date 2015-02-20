#ifndef LEX_H
#define LEX_H

#include <stdlib.h>
#include <string.h>

enum type
{
	STRING = 0,
	VALUE = 1,
	LIST = 2,
	IDENTIFIER = 3,
	OPAREN = 4,
	CPAREN = 5
};

typedef enum type type;

struct token
{
	char* tok_str;
	type tok_type;
};

typedef struct token token;

struct token_array
{
	token* tok_array;
	unsigned int len;
};

typedef struct token_array token_array;

token_array lex(char* str);
token_array inc_tok_array(token_array tokens);
token_array add_to_tok_array(token_array tokens, char* new_str, unsigned int new_str_len, type tok_type);
token_array lex_str(token_array tokens, char* unlexed_str);

#endif
