#include "../../includes/minishell.h" 


// Function to determine token type
int get_token_type(char *str) {
    if (strcmp(str, "|") == 0)
        return PIPE;
    else if (strcmp(str, ">") == 0)
        return REDIRECT_OUT;  
    else if (strcmp(str, ">>") == 0)
        return APPEND;
    else if (strcmp(str, "<") == 0)
        return REDIRECT_IN;
    else if (strcmp(str, "<<") == 0)
        return HEREDOC;
    else if (is_valid_word(str))  // A function to check valid words (commands, filenames)
        return WORD;
    else
        return INVALID;  // Anything else is considered invalid
}

// Create a new token
t_token *create_token(char *str, int type) {
    t_token *new_token = malloc(sizeof(t_token));
    if (!new_token)
        return NULL;
    new_token->str = strdup(str);  // Use strdup for copying the string
    new_token->type = type;
    new_token->next = NULL;
    return new_token;
}

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

// Free the token list
void free_token_list(t_token *token_list) {
    t_token *current = token_list;
    t_token *next;

    while (current != NULL) {
        next = current->next;
        free(current->str);  // Free the token string
        free(current);       // Free the token struct
        current = next;
    }
}

int is_valid_word(char *str) {
    // Allow all characters except separators and whitespaces
    for (int i = 0; str[i]; i++) {
        if (is_separator(str[i]) || is_whitespace(str[i])) {
            return 0;  // Not a valid word
        }
    }
    return 1;  // Valid word
}
