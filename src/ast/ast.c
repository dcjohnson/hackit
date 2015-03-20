#include "ast.h"

void init_ast(ast *ast_head) {
	ast_head->child_nodes = NULL;
	ast_head->parent_node = NULL;
	ast_head->child_count = 0;
}

void init_data_list(data_list *list) {
	list->list = NULL;
	list->len = 0;
}

void inc_data_list(data_list *list, ast_data data) {
	list->len++;
	list->list = realloc(list->list, sizeof(ast_data) * list->len);
	list->list[list->len - 1] = data;
}

void dec_data_list(data_list *list) {
	list->len--;
	list->list = realloc(list->list, sizeof(ast_data) * list->len);
}

void insert_node(ast *parent, ast new_ast_node) {
	parent->child_count++;
	parent->child_nodes = realloc(parent->child_nodes, sizeof(ast) * parent->child_count);
	parent->child_nodes[parent->child_count - 1] = new_ast_node;
	parent->child_nodes[parent->child_count - 1].parent_node = parent;
}

void free_ast(ast *tree) {
	for (int index = 0; index < tree->child_count; index++) {
		if (tree->child_nodes[index].child_count > 0) {
			free_ast(&tree->child_nodes[index]);
		}
	}
	free(tree->child_nodes);
}
