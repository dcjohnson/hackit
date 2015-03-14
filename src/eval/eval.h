#ifndef EVAL_H
#define EVAL_H

#import "../ast/ast.h"
#import <stdlib.h>

struct tree_loc {
	ast *node_ptr;
	int cur_child;
};

typedef struct tree_loc tree_loc;

struct tree_loc_stack {
	tree_loc node;
	struct tree_loc_stack *next;
};

typedef struct tree_loc_stack tree_loc_stack;

void eval(ast *tree);
tree_loc_stack *push_tree_loc_stack(tree_loc_stack *stack, ast *new_node);
tree_loc_stack *pop_tree_loc_stack(tree_loc_stack *stack);

#endif
