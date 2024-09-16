#include "../../includes/minishell.h" 


// Validate the token list for correct shell syntax
int validate_tokens(t_token *token_list) {
    t_token *current = token_list;

    if (!current) {
        // If the list is empty, it's valid (or you may consider it invalid).
        return SUCCESS;
    }

    // First token must be a command (WORD), not a pipe or redirection
    if (current->type != WORD) {
        printf("Syntax error: command cannot start with '%s'\n", current->str);
        return FAILURE;
    }

    while (current) {
        if (current->type == PIPE) {
            // Check that the pipe is followed by a valid command (WORD)
            if (!current->next || current->next->type != WORD) {
                printf("Syntax error: pipe '|' must be followed by a command.\n");
                return FAILURE;
            }
        }
        else if (current->type == REDIRECT_OUT || 
                 current->type == REDIRECT_IN || current->type == APPEND || current->type == HEREDOC) {
            // Check that redirection is followed by a file (WORD)
            if (!current->next || current->next->type != WORD) {
                printf("Syntax error: redirection '%s' must be followed by a file.\n", current->str);
                return FAILURE;
            }
        }
        else if (current->type == INVALID) {
            // Handle invalid tokens
            printf("Syntax error: Invalid token '%s'\n", current->str);
            return FAILURE;
        }

        // Move to the next token
        current = current->next;
    }

    // If no syntax errors, return success
    return SUCCESS;
}
