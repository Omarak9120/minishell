#include "minishell.h"

// Main function to start the lexing process
t_token *tokenize_input(char *input) {
    t_token *token_list = NULL;
    int i = 0;

    while (input[i]) {
        if (is_whitespace(input[i]))
            i++;  // Skip whitespaces
        else if (is_separator(input[i]))
            add_token(&token_list, create_separator_token(input, &i));
        else
            add_token(&token_list, create_word_token(input, &i));
    }
    return token_list;
}
