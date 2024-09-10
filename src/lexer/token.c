#include "minishell.h"

// Create a new token (basic linked list)
t_token *create_token(char *str, int type) {
    t_token *new_token = malloc(sizeof(t_token));
    if (!new_token)
        return NULL;
    new_token->str = ft_strdup(str);
    new_token->type = type;
    new_token->next = NULL;
    return new_token;
}

// Free the token
void free_token(t_token *token) {
    if (token) {
        free(token->str);
        free(token);
    }
}
