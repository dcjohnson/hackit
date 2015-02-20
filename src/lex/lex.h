#ifndef LEX_H
#define LEX_H

#include <stdlib.h>
#include <string.h>

struct tok_struct
{
	char** tok_array;
	unsigned int tok_len;
};

typedef struct tok_struct tok_struct;

tok_struct lex_str(char* str);
void inc_tok_struct(tok_struct* tokens);
void add_to_tok_struct(tok_struct* tokens, char* new_str, unsigned int new_str_len);

#endif
