#include "builtins.h"

const char *core[] = {"+", "add", NULL};
core_func_ptr core_ptr[] = {add, add};

ast_data add(ast *params) {
	ast_data result;
	result.type = INT_DATA;

	long long int col_int = 0;
	long double col_doub = 0.0;
	for (int index = 0; index < params->child_count; index++) {
		if (params->child_nodes[index].data.type == INT_DATA) {
			col_int += params->child_nodes[index].data.val.int_val;
		} else if (params->child_nodes[index].data.type == FLOAT_DATA) {
			col_doub += params->child_nodes[index].data.val.float_val;
			result.type = FLOAT_DATA;
		}
	}
	if (result.type == INT_DATA) {
		result.val.int_val = col_int;
	} else if (result.type == FLOAT_DATA) {
		result.val.float_val = col_doub;
		result.val.float_val += col_int;
	}

	return result;
}

core_func_ptr get_core_ptr(token tok) {
	int index = 0;
	while(core[index] != NULL) {
		if(strcmp(core[index], tok.tok_data.tok_str) == 0) {
			return core_ptr[index];
		}
	}

	return NULL;
}
