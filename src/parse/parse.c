#include "parse.h"

char *parse(token_array *tokens, ast *tree) {
	char *ok_err_mesg = NULL;

	ast **cur_node = &tree;
	for (int index = 0; index < tokens->len; index++) {
		parse_token(tokens->tok_array[index], cur_node);
	}

	return ok_err_mesg;
}

void parse_token(token tok, ast **cur_node) {
	static ast_data *list = NULL;
	static int *list_len = NULL;
	static int len = 0;
	ast new_node;

	switch (tok.tok_type) {
		case STRING:
			init_ast(&new_node);
			parse_string(tok, &new_node);
			break;
		case VALUE:
			init_ast(&new_node);
			parse_value(tok, &new_node);
			break;
		case LIST:
			len++;
			list = realloc(list, sizeof(ast_data) * len);
			list_len = realloc(list_len, sizeof(int) * len);
			init_data_list(&list[len - 1].val.list);
			list_len[len - 1] = tok.tok_data.list_len;
			break;
		case IDENTIFIER:
			parse_ident(tok, *cur_node);
			break;
		case OPAREN:
			init_ast(&new_node);
			insert_node(*cur_node, new_node);
			*cur_node = &(*cur_node)->child_nodes[(*cur_node)->child_count - 1];
			break;
		case CPAREN:
			*cur_node = (*cur_node)->parent_node;
			break;
	}

	if (tok.tok_type == STRING || tok.tok_type == VALUE) {
		if (len > 0) {
			list[len - 1].val.list.len++;
			list[len - 1].val.list.list = realloc(list[len - 1].val.list.list, sizeof(ast_data) * list[len - 1].val.list.len);
			list[len - 1].val.list.list[list[len - 1].val.list.len - 1] = new_node.data;
		} else {
			insert_node(*cur_node, new_node);
		}
	}

	while(len > 1 && list[len - 1].val.list.len == list_len[len - 1]) {
		list[len - 2].val.list.len++;
		list[len - 2].val.list.list = realloc(list[len - 2].val.list.list, sizeof(ast_data) * list[len - 2].val.list.len);
		list[len - 2].val.list.list[list[len - 2].val.list.len - 1] = list[len - 1];
		len--;
		list = realloc(list, sizeof(ast_data) * len);
		list_len = realloc(list_len, sizeof(int) * len);
	}

	if (len == 1 && list[len - 1].val.list.len == list_len[len - 1]) {
		init_ast(&new_node);
		new_node.data = list[len - 1];
		insert_node(*cur_node, new_node);
		len--;
		list = realloc(list, sizeof(ast_data) * len);
		list_len = realloc(list_len, sizeof(int) * len);
	}
}

int parse_string(token tok, ast *ast_node) {
	if (tok.tok_type != STRING) {
		return -1;
	}

	ast_node->data.val.string_val = malloc(sizeof(char) * strlen(tok.tok_data.tok_str));
	ast_node->data.type = STRING_DATA;
	strcpy(ast_node->data.val.string_val, tok.tok_data.tok_str);

	return 1;
}

int parse_value(token tok, ast *ast_node) {
	if (tok.tok_type != VALUE) {
		return -1;
	}

	if (strchr(tok.tok_data.tok_str, '.') == NULL) {
		ast_node->data.val.int_val = strtoll(tok.tok_data.tok_str, NULL, 10);
		ast_node->data.type = INT_DATA;
	} else {
		ast_node->data.val.float_val = strtold(tok.tok_data.tok_str, NULL);
		ast_node->data.type = FLOAT_DATA;
	}

	return 1;
}

int parse_ident(token tok, ast *ast_node) {
	if(tok.tok_type != IDENTIFIER) {
		return -1;
	}

	if (set_builtin(tok, ast_node) == 1) {
		ast_node->data.type = BUILTIN_FUNC;
	} else {
		return -1;
	}

	return 1;
}

int set_builtin(token tok, ast *ast_node) {
	core_func_ptr func_ptr = get_core_ptr(tok);
	if (func_ptr == NULL) {
		return -1;
	} else {
		ast_node->data.val.builtin = func_ptr;
		return 1;
	}
}
