#include "parse.h"

char* parse(token_array* tokens, ast* tree)
{
	char* ok_err_mesg = NULL;

	ast** cur_node = &tree;
	for(int index = 0; index < tokens->len; index++)
	{
		parse_token(tokens->tok_array[index], cur_node);
	}

	return ok_err_mesg;
}

void parse_token(token tok, ast** cur_node)
{
	static ast** list_nodes = NULL;
	static int list_nodes_len = 0;
	ast new_node;
	ast* list_val = NULL;
	switch(tok.tok_type)
	{
		case STRING:
			init_ast(&new_node);
			parse_string(tok, &new_node);
			list_val = insert_node(*cur_node, new_node);
			break;
		case VALUE:
			init_ast(&new_node);
			parse_value(tok, &new_node);
			list_val = insert_node(*cur_node, new_node);
			break;
		case LIST:
			list_nodes_len++;
			list_nodes = realloc(list_nodes, sizeof(ast*) * list_nodes_len);
			init_ast(&new_node);
			new_node.data.type = LIST_DATA;
			list_nodes[list_nodes_len - 1] = insert_node(*cur_node, new_node);
			break;
		case IDENTIFIER:
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

	if(list_nodes_len == 0)
	{
		list_nodes[list_nodes_len - 1]->
	}
}

int parse_string(token tok, ast* ast_node)
{
	if(tok.tok_type != STRING)
	{
		return -1;
	}

	ast_node->data.val.string_val = malloc(sizeof(char) * strlen(tok.tok_data.tok_str));
	ast_node->data.type = STRING_DATA;
	strcpy(ast_node->data.val.string_val, tok.tok_data.tok_str);

	return 1;
}

int parse_value(token tok, ast* ast_node)
{
	if(tok.tok_type != VALUE)
	{
		return -1;
	}

	if(strchr(tok.tok_data.tok_str, '.') == NULL)
	{
		ast_node->data.val.int_val = strtoll(tok.tok_data.tok_str, NULL, 10);
		ast_node->data.type = INT_DATA;
	}
	else
	{
		ast_node->data.val.float_val = strtold(tok.tok_data.tok_str, NULL);
		ast_node->data.type = FLOAT_DATA;
	}

	return 1;
}
