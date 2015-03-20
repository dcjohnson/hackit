#include "builtins.h"

const char *core[] = {"add", "print", NULL};
core_func_ptr core_ptr[] = {add, print};

struct ast_data *add(ast *params, struct ast_data *new_data) {
	new_data->type = INT_DATA;

	long long int col_int = 0;
	long double col_doub = 0.0;
	for (int index = 0; index < params->child_count; index++) {
		if (params->child_nodes[index].data.type == INT_DATA) {
			col_int += params->child_nodes[index].data.val.int_val;
		} else if (params->child_nodes[index].data.type == FLOAT_DATA) {
			col_doub += params->child_nodes[index].data.val.float_val;
			new_data->type = FLOAT_DATA;
		}
	}
	if (new_data->type == INT_DATA) {
		new_data->val.int_val = col_int;
	} else if (new_data->type == FLOAT_DATA) {
		new_data->val.float_val = col_doub;
		new_data->val.float_val += col_int;
	}
	return new_data;
}

struct ast_data *print(ast *params, struct ast_data *new_data) {
	for (int index = 0; index < params->child_count; index++) {
		if (params->child_nodes[index].data.type == INT_DATA) {
			printf("%lli\n", params->child_nodes[index].data.val.int_val);
		} else if (params->child_nodes[index].data.type == FLOAT_DATA) {
			printf("%Lf\n", params->child_nodes[index].data.val.float_val);
		} else if (params->child_nodes[index].data.type == STRING_DATA) {
			printf("%s\n", params->child_nodes[index].data.val.string_val);
		}
	}
	return NULL;
}

core_func_ptr get_core_ptr(token tok) {
	int index = 0;
	while(core[index] != NULL) {
		if(strcmp(core[index], tok.tok_data.tok_str) == 0) {
			return core_ptr[index];
		}
		index++;
	}

	return NULL;
}
