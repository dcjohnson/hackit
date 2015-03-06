#ifndef LEX_H
#define LEX_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

union data {
	char *tok_str;
	int list_len; // Number of tokens following this token that are in the list.
};

typedef union data data;

enum type {
	STRING = 0,
	VALUE = 1,
	LIST = 2, // Can only contain Strings, Values, and Lists
	IDENTIFIER = 3,
	OPAREN = 4,
	CPAREN = 5
};

typedef enum type type;

enum err {
	DEFAULT = 0,
	AMBIGUOUS_STRING = 1,
	AMBIGUOUS_VALUE = 2,
	AMBIGUOUS_LIST = 3,
	UNRECOGNIZED_CHARACTER = 4
};

typedef enum err err;

struct token {
	data tok_data;
	type tok_type;
};

typedef struct token token;

struct token_array {
	token *tok_array;
	int len;
};

typedef struct token_array token_array;

char *lex(token_array *tokens, char *str);
char *ret_err_str(err err_type);
char *lex_token(token_array *tokens, char *src, char *cur_char);
int lex_str(token_array *tokens, char *unlexed_str);
int lex_value(token_array *tokens, char *unlexed_value);
int lex_ident(token_array *tokens, char *unlexed_ident);
int add_non_list(token_array *tokens, char *new_str, int new_str_len, type tok_type);
void free_tok_array(token_array *toks);
void inc_tok_array(token_array *tokens);
void lex_identifier(token_array *tokens, char *unlexed_iden);
void add_list(token_array *tokens);

#endif
