#include "lex.h"

char *lex(token_array *tokens, char *str) {
	tokens->tok_array = NULL;
	tokens->len = 0;
	char cur_char;
	char *err_mesg = lex_token(tokens, str, &cur_char);

	while (!(err_mesg != NULL || cur_char == '\0')) {
		err_mesg = lex_token(tokens, NULL, &cur_char);
	}
	return err_mesg;
}

char *lex_token(token_array *tokens, char *src, char *cur_char) {
	static char *static_str = NULL;
	static int index = 0;
	static int *list_tokens_location = NULL;
	static int tok_len = 0;
	int list_tok_to_inc = 0;
	if (src != NULL) {
		free(list_tokens_location);
		index = 0;
		static_str = src;
		list_tokens_location = NULL;
		tok_len = 0;
	}
	char *ok_err_str = NULL;

	if (static_str[index] == '"') {
		int str_len = lex_str(tokens, &static_str[index]);
		if (str_len == -1) {
			ok_err_str = ret_err_str(AMBIGUOUS_STRING);
		} else {
			index++;
			add_non_list(tokens, &static_str[index], str_len, STRING);
			index += str_len;
			list_tok_to_inc = 1;
		}
	} else if (((int)static_str[index] >= (int)'0' && (int)static_str[index] <= (int)'9') || static_str[index] == '.') {
		int val_len = lex_value(tokens, &static_str[index]);
		if (val_len == -1) {
			ok_err_str = ret_err_str(AMBIGUOUS_VALUE);
		} else {
			add_non_list(tokens, &static_str[index], val_len, VALUE);
			index += (val_len - 1);
			list_tok_to_inc = 1;
		}
	} else if (static_str[index] == '(') {
		add_non_list(tokens, &static_str[index], 1, OPAREN);
	} else if (static_str[index] == ')') {
		if (tok_len > 0) {
			tok_len--;
			list_tokens_location =
			realloc(list_tokens_location, sizeof(int) * tok_len);
		} else {
			add_non_list(tokens, &static_str[index], 1, CPAREN);
		}
	} else if (static_str[index] == '\'') {
		if (static_str[index + 1] != '(') {
			ok_err_str = ret_err_str(AMBIGUOUS_LIST);
		} else {
			add_list(tokens);
			tok_len++;
			list_tokens_location =
			realloc(list_tokens_location, sizeof(int) * tok_len);
			list_tokens_location[tok_len - 1] = tokens->len - 1;
			list_tok_to_inc = 2;
			index++;
		}
	} else if (((int)static_str[index] >= (int)'a' && (int)static_str[index] <= (int)'z') ||
				((int)static_str[index] >= (int)'A' && (int)static_str[index] <= (int)'Z') ||
				static_str[index] == '_') {
		int val_len = lex_ident(tokens, &static_str[index]);
		add_non_list(tokens, &static_str[index], val_len, VALUE);
		index += (val_len - 1);
		if (tok_len > 0) {
			ok_err_str = ret_err_str(AMBIGUOUS_LIST);
		}
	} else if (static_str[index] != ' ' && static_str[index] != '\n') {
		ok_err_str = ret_err_str(UNRECOGNIZED_CHARACTER);
	}

	if (tok_len > 0) {
		if ((list_tok_to_inc == 2 && tok_len > 1) ||
		(list_tok_to_inc == 1 && tok_len > 0)) {
			tokens->tok_array[list_tokens_location[tok_len - list_tok_to_inc]].tok_data.list_len++;
		}
	}

	index++;
	*cur_char = static_str[index];

	if (*cur_char == '\0' && tok_len > 0) {
		ok_err_str = ret_err_str(AMBIGUOUS_LIST);
	}

	return ok_err_str;
}

void inc_tok_array(token_array *tokens) {
	tokens->len++;
	tokens->tok_array = realloc(tokens->tok_array, sizeof(token) * tokens->len);
}

void add_list(token_array *tokens) {
	inc_tok_array(tokens);
	tokens->tok_array[tokens->len - 1].tok_data.list_len = 0;
	tokens->tok_array[tokens->len - 1].tok_type = LIST;
}

int add_non_list(token_array *tokens, char *new_str, int new_str_len, type tok_type) {
	if (tok_type == LIST) {
		return -1;
	}
	inc_tok_array(tokens);
	tokens->tok_array[tokens->len - 1].tok_data.tok_str =
	malloc(sizeof(char) * (new_str_len + 1));
	memcpy(tokens->tok_array[tokens->len - 1].tok_data.tok_str, new_str, new_str_len);
		tokens->tok_array[tokens->len - 1].tok_data.tok_str[new_str_len] = '\0';
		tokens->tok_array[tokens->len - 1].tok_type = tok_type;
		return 1;
}

int lex_str(token_array *tokens, char *unlexed_str) {
	int str_len = 1;
	char cur_char = unlexed_str[str_len];
	do {
		if (cur_char == '\\' && unlexed_str[str_len + 1] != '\0') {
			str_len++;
		} else if (cur_char == '"') {
			str_len--;
			return str_len;
		}
		str_len++;
		cur_char = unlexed_str[str_len];
	} while (cur_char != '\0');
	return -1;
}

int lex_value(token_array *tokens, char *unlexed_value) {
	int val_len = 1;
	char cur_digit = unlexed_value[val_len];
	int decimal = unlexed_value[0] == '.' ? 1 : 0;
	for (;;) {
		if (cur_digit == '.') {
			if (decimal == 1) {
				if (val_len == 1) {
					return -1;
				} else {
					break;
				}
			} else {
				decimal = 1;
			}
		} else if (!((int)cur_digit >= (int)'0' && (int)cur_digit <= (int)'9')) {
			if (val_len == 1 && decimal == 1) {
				return -1;
			} else {
				break;
			}
		}
		val_len++;
		cur_digit = unlexed_value[val_len];
	}
	return val_len;
}

int lex_ident(token_array *tokens, char *unlexed_ident) {
	int val_len = 0;
	char cur_char = unlexed_ident[val_len];
	for (;;) {
		if (((int)cur_char >= (int)'a' && (int)cur_char <= (int)'z') ||
			((int)cur_char >= (int)'A' && (int)cur_char <= (int)'Z') ||
		cur_char == '_') {
			val_len++;
			cur_char = unlexed_ident[val_len];
		} else {
			break;
		}
	}
	return val_len;
}

void free_tok_array(token_array *toks) {
	for (int index = 0; index < toks->len; index++) {
		if (toks->tok_array[index].tok_type != LIST) {
			free(toks->tok_array[index].tok_data.tok_str);
		}
	}
	free(toks->tok_array);
	toks->tok_array = NULL;
	toks->len = 0;
}

char *ret_err_str(err err_type) {
	switch (err_type) {
		case AMBIGUOUS_STRING:
			return "Ambiguous string declaration";
		case AMBIGUOUS_VALUE:
			return "Ambiguous value declaration";
		case AMBIGUOUS_LIST:
			return "Ambiguous list declaration";
		case UNRECOGNIZED_CHARACTER:
			return "Unrecognized character";
		default:
			return "Error";
	}
}
