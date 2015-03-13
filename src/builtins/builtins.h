#ifndef BUILTINS_H
#define BUILTINS_H

#include "../ast/ast.h"
#include "../lex/lex.h"
#include <stdio.h>

typedef struct ast_data *(*core_func_ptr)(ast *params, struct ast_data *new_data);
core_func_ptr get_core_ptr(token tok);
struct ast_data *add(ast *params, struct ast_data *new_data);
struct ast_data *print(ast *params, struct ast_data *new_data);

#endif
