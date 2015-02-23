#ifndef LEX_H
#define LEX_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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

enum err
{
	DEFAULT = 0,
	AMBIGUOUS_STRING = 1,
	AMBIGUOUS_VALUE = 2,
	UNRECOGNIZED_CHARACTER = 3
};

typedef enum err err;

struct token
{
	char* tok_str;
	type tok_type;
};

typedef struct token token;

struct token_array
{
	token* tok_array;
	int len;
};

typedef struct token_array token_array;

char* lex(token_array* tokens, char* str);
char* ret_err_str(err err_type);
int lex_str(token_array* tokens, char* unlexed_str);
int lex_value(token_array* tokens, char* unlexed_value);
int lex_ident(token_array* tokens, char* unlexed_ident);
void inc_tok_array(token_array* tokens);
void add_to_tok_array(token_array* tokens, char* new_str, int new_str_len, type tok_type);
void free_tok_array(token_array* toks);
void lex_identifier(token_array* tokens, char* unlexed_iden);

#endif
