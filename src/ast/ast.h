#ifndef AST_H
#define AST_H

#include <stdlib.h>
#include <stdio.h>

enum data_type
{
	INT_DATA = 0,
	DOUBLE_DATA = 1,
	LIST_DATA = 2,
	STRING_DATA = 3,
	FUNC_DATA = 4
};

typedef enum data_type data_type;

union value
{
	long long int int_val;
	long double double_val;
	char* string_val;
	struct ast_data* list;
	struct ast* func_ptr;
};

typedef union value value;

struct ast_data
{
	value val;
	data_type type;
};

typedef struct ast_data ast_data;

struct ast
{
	struct ast* child_nodes;
	ast_data* data; // Null if start state.
	int child_count;
};

typedef struct ast ast;

void init_ast(ast* ast_head);
void insert_node(ast* parent, ast new_ast_node);

#endif
