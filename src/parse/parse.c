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
	ast new_node;
	switch(tok.tok_type)
	{
		case STRING:
			init_ast(&new_node);
			parse_string(tok, &new_node);
			insert_node(*cur_node, new_node);
			break;
		case VALUE:
			break;
		case LIST:
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
}

int parse_string(token tok, ast* ast_node)
{
	if(tok.tok_type != STRING)
	{
		return -1;
	}

	ast_node->data.val.string_val = malloc(sizeof(char) * strlen(tok.tok_data.tok_str));
	strcpy(ast_node->data.val.string_val, tok.tok_data.tok_str);

	return 1;
}

int parse_value(token tok, ast* ast_node)
{
	if(tok.tok_type != VALUE)
	{
		return -1;
	}

	return 1;
}
