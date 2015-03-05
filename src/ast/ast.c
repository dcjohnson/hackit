#include "ast.h"

void init_ast(ast* ast_head)
{
	ast_head->child_nodes = NULL;
	ast_head->parent_node = NULL;
	ast_head->child_count = 0;
}

ast* insert_node(ast* parent, ast new_ast_node)
{
	parent->child_count++;
	parent->child_nodes = realloc(parent->child_nodes, sizeof(ast) * parent->child_count);
	parent->child_nodes[parent->child_count - 1] = new_ast_node;
	parent->child_nodes[parent->child_count - 1].parent_node = parent;
	return &(parent->child_nodes[parent->child_count - 1]);
}
