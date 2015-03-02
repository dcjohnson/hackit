#include "parse.h"

char* parse(token_array* tokens, ast* tree)
{
	char* ok_err_mesg = NULL;

	ast cur_node = *tree;
	for(int index = 0; index < tokens->len; index++)
	{
		cur_node = parse_token(tokens->tok_array[index], &cur_node);
	}

	return ok_err_mesg;
}

ast parse_token(token tok, ast* cur_node)
{
	ast ret_node;
	switch(tok.tok_type)
	{
		case STRING:
			break;
		case VALUE:
			break;
		case LIST:
			break;
		case IDENTIFIER:
			break;
		case OPAREN:
			init_ast(&ret_node);
			insert_node(cur_node, ret_node);
			break;
		case CPAREN:
			ret_node = *cur_node->parent_node;
			break;
	}
	return ret_node;
}
