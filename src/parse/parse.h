#ifndef PARSE_H
#define PARSE_H

#include "../ast/ast.h"
#include "../lex/lex.h"

char* parse(token_array* tokens, ast* tree);
ast parse_token(token tok, ast* cur_node);

#endif
