#include "ast.h"

void init_ast(ast* ast_head)
{
	ast_head = malloc(sizeof(ast));
	ast_head->child_nodes = NULL;
	ast_head->data = NULL;
}

int insert_node(ast* ast_head, ast* new_ast_node)
{
	return 1;
}
