#import "eval.h"

void eval(ast *tree) {
	tree_loc_stack *stack = NULL;
	ast *cur_node = tree;
	do {
		stack = push_tree_loc_stack(stack, cur_node);
	} while (stack != NULL);
}

tree_loc_stack *push_tree_loc_stack(tree_loc_stack *stack, ast *new_node) {
	if (stack == NULL) {
		stack = malloc(sizeof(tree_loc_stack));
		stack->next = NULL;
		stack->node.node_ptr = new_node;
		stack->node.cur_child = 0;
	} else {
		tree_loc_stack *new_head = NULL;
		new_head = malloc(sizeof(tree_loc_stack));
		new_head->next = stack;
		new_head->node.node_ptr = new_node;
		new_head->node.cur_child = 0;
		stack = new_head;
	}
	return stack;
}

tree_loc_stack *pop_tree_loc_stack(tree_loc_stack *stack) {
	if (stack != NULL) {
		tree_loc_stack *new_head = stack->next;
		free(stack);
		stack = new_head;
	}
	return stack;
}
