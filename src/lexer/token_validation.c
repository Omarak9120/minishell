#include "minishell.h"

// Validate the token list for correct shell syntax
int validate_tokens(t_token *token_list) {
    t_token *current = token_list;

    while (current) {
        if (current->type == PIPE && (!current->next || current->next->type == PIPE))
            return FAILURE; // Pipe must be followed by a valid command
        current = current->next;
    }
    return SUCCESS;
}
