#include "lex.h"

char* lex(token_array* tokens, char* str)
{
	char* ok_err_str = NULL;
	tokens->tok_array = NULL;
	tokens->len = 0;
	int index = 0;

	while(str[index] != '\0')
	{
		if(str[index] == '"')
		{
			int str_len = lex_str(tokens, &str[index]);
			if(str_len == -1)
			{
				ok_err_str = ret_err_str(AMBIGUOUS_STRING);
				break;
			}
			add_to_tok_array(tokens, &str[index], str_len, STRING);
			index += (str_len - 1);
		}
		else if(((int)str[index] >= (int)'0' && (int)str[index] <= (int)'9') || str[index] == '.')
		{
			int val_len = lex_value(tokens, &str[index]);
			if(val_len == -1)
			{
				ok_err_str = ret_err_str(AMBIGUOUS_VALUE);
				break;
			}
			add_to_tok_array(tokens, &str[index], val_len, VALUE);
			index += (val_len - 1);
		}
		else if(str[index] == '(')
		{
			add_to_tok_array(tokens, &str[index], 1, OPAREN);
		}
		else if(str[index] == ')')
		{
			add_to_tok_array(tokens, &str[index], 1, CPAREN);
		}
		index++;
	}
	return ok_err_str;
}

void inc_tok_array(token_array* tokens)
{
	tokens->len++;
	tokens->tok_array = realloc(tokens->tok_array, sizeof(token) * tokens->len);
	tokens->tok_array[tokens->len - 1].tok_str = NULL;
}

void add_to_tok_array(token_array* tokens, char* new_str, int new_str_len, type tok_type)
{
	inc_tok_array(tokens);
	tokens->tok_array[tokens->len - 1].tok_str = malloc(sizeof(char) * (new_str_len + 1));
	memcpy(tokens->tok_array[tokens->len - 1].tok_str, new_str, new_str_len);
	tokens->tok_array[tokens->len - 1].tok_str[new_str_len] = '\0';
	tokens->tok_array[tokens->len - 1].tok_type = tok_type;
}

int lex_str(token_array* tokens, char* unlexed_str)
{
	int str_len = 1;
	char cur_char = unlexed_str[str_len];
	do
	{
		if(cur_char == '\\' && unlexed_str[str_len + 1] != '\0')
		{
			str_len++;
		}
		else if(cur_char == '"')
		{
			str_len++;
			return str_len;
		}
		str_len++;
		cur_char = unlexed_str[str_len];
	} while(cur_char != '\0');
	return -1;
}

int lex_value(token_array* tokens, char* unlexed_value)
{
	int val_len = 1;
	char cur_digit = unlexed_value[val_len];
	int decimal = unlexed_value[0] == '.' ? 1 : 0;
	for(;;)
	{
		if(cur_digit == '.')
		{
			if(decimal == 1)
			{
				if(val_len == 1)
				{
					return -1;
				}
				else
				{
					break;
				}
			}
			else
			{
				decimal = 1;
			}
		}
		else if(!((int)cur_digit >= (int)'0' && (int)cur_digit <= (int)'9'))
		{
			if(val_len == 1 && decimal == 1)
			{
				return -1;
			}
			else
			{
				break;
			}
		}
		val_len++;
		cur_digit = unlexed_value[val_len];
	}
	return val_len;
}

void free_tok_array(token_array* toks)
{
	for(int index = 0; index < toks->len; index++)
	{
		free(toks->tok_array[index].tok_str);
	}
	free(toks->tok_array);
	toks->tok_array = NULL;
	toks->len = 0;
}

char* ret_err_str(err err_type)
{
	switch (err_type)
	{
		case AMBIGUOUS_STRING:
			return "Ambiguous string declaration";
		case AMBIGUOUS_VALUE:
			return "Ambiguous value declaration";
		default:
			return "Error";
	}
}
