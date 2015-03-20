#import "eval.h"

void eval(ast *tree) {
	tree_loc_stack *stack = NULL;
	do {
		if (stack == NULL) {
			stack = push_tree_loc_stack(stack, tree);
		} else if (stack->node.cur_child < stack->node.node_ptr->child_count) {
			stack->node.cur_child++;
			stack = push_tree_loc_stack(stack, &stack->node.node_ptr->child_nodes[stack->node.cur_child - 1]);
		} else if (stack->node.node_ptr->child_count == 0 || stack->node.node_ptr->child_count == stack->node.cur_child) {
			if (stack->node.node_ptr->data.type == BUILTIN_FUNC) {
				ast_data new_data;
				ast_data *new_data_ptr = (stack->node.node_ptr->data.val.builtin)(stack->node.node_ptr, &new_data);
				if (new_data_ptr != NULL) {
					stack->node.node_ptr->data = new_data;
				} else {
					stack = pop_tree_loc_stack(stack);
				}
			} else {
				stack = pop_tree_loc_stack(stack);
			}
		}
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
