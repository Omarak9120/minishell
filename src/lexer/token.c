#include "../../includes/minishell.h"

// // Add token to the end of the list
// void add_token(t_token **token_list, t_token *new_token) {
//     t_token *current = *token_list;

//     if (!current)
//         *token_list = new_token;
//     else {
//         while (current->next)
//             current = current->next;
//         current->next = new_token;
//     }
// }


// // Create a new token (basic linked list)
// t_token *create_token(char *str, int type) {
//     t_token *new_token = malloc(sizeof(t_token));
//     if (!new_token)
//         return NULL;
//     new_token->str = ft_strdup(str);
//     new_token->type = type;
//     new_token->next = NULL;
//     return new_token;
// }

// // Free the token
// void free_token(t_token *token) {
//     if (token) {
//         free(token->str);
//         free(token);
//     }
// }
