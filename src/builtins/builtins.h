#ifndef BUILTINS_H
#define BUILTINS_H

#include "../ast/ast.h"
#include "../lex/lex.h"
#include <stdio.h>

typedef ast_data (*core_func_ptr)(ast *params);
core_func_ptr get_core_ptr(token tok);
ast_data add(ast *params);

#endif
