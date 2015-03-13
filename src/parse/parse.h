#ifndef PARSE_H
#define PARSE_H

#include "../ast/ast.h"
#include "../lex/lex.h"
#include "../builtins/builtins.h"

char *parse(token_array *tokens, ast *tree);
int parse_string(token tok, ast *ast_node);
int parse_value(token tok, ast *ast_node);
int parse_ident(token tok, ast *ast_node);
int set_builtin(token tok, ast *ast_node);
ast *func_search(token tok, ast *ast_node);
void parse_token(token tok, ast **cur_node);

#endif
