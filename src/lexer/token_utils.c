#include "minishell.h"

// Add token to the end of the list
void add_token(t_token **token_list, t_token *new_token) {
    t_token *current = *token_list;

    if (!current)
        *token_list = new_token;
    else {
        while (current->next)
            current = current->next;
        current->next = new_token;
    }
}
