#ifndef PARSE_H
#define PARSE_H

#include "../ast/ast.h"
#include "../lex/lex.h"

char* parse(token_array* tokens, ast* tree);
void parse_token(token tok, ast** cur_node);
int parse_string(token tok, ast* ast_node);
int parse_value(token tok, ast* ast_node);

#endif
