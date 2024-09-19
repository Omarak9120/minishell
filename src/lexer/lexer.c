#include "../../includes/minishell.h" 


// Main function to start the lexing process
t_token *tokenize_input(char *input) {
    t_token *token_list = NULL;
    int i = 0;

    while (input[i]) {
        if (is_whitespace(input[i])) {
            i++;  // Skip whitespaces
        }
        else if (input[i] == '"') {
            t_token *token = create_quoted_token(input, &i, '"');
            if (!token) {
                free_token_list(token_list);  // Free the list in case of an error
                return NULL;  // Return NULL if there's an unmatched quote
            }
            add_token(&token_list, token);
        }
        else if (input[i] == '\'') {
            t_token *token = create_quoted_token(input, &i, '\'');
            if (!token) {
                free_token_list(token_list);  // Free the list in case of an error
                return NULL;  // Return NULL if there's an unmatched quote
            }
            add_token(&token_list, token);
        }
        else {
            t_token *token = create_general_token(input, &i);
            if (!token) {
                free_token_list(token_list);  // Free the list in case of an error
                return NULL;  // Return NULL in case of any other error
            }
            add_token(&token_list, token);
        }
    }
    return token_list;
}

// Create a token for quoted strings (everything between quotes)
t_token *create_quoted_token(char *input, int *i, char quote_type) {
    char *quoted_str = NULL;
    int capacity = 256;
    int j = 0;

    quoted_str = malloc(capacity * sizeof(char));
    if (!quoted_str) return NULL;

    (*i)++;  // Skip the opening quote

    // Read characters until the closing quote is found
    while (input[*i]) {
        if (input[*i] == quote_type) {
            (*i)++;  // Skip the closing quote
            break;
        }

        quoted_str[j++] = input[*i];  // Add the regular character
        (*i)++;

        // Resize buffer if necessary
        if (j >= capacity) {
            capacity *= 2;
            char *new_str = realloc(quoted_str, capacity * sizeof(char));
            if (!new_str) {
                free(quoted_str);
                return NULL; // Handle allocation failure
            }
            quoted_str = new_str;
        }
    }

    // Check if the closing quote is missing
    if (input[*i - 1] != quote_type) {
        printf("Syntax error: unmatched %c quote\n", quote_type);
        free(quoted_str);
        return NULL;
    }

    quoted_str[j] = '\0';  // Null-terminate the string

    // Return a single token containing the entire quoted string
    t_token *token = create_token(quoted_str, WORD);
    free(quoted_str);
    return token;
}



t_token *create_general_token(char *input, int *i) {
    char *token_str = NULL;
    int capacity = 256;
    int j = 0;

    token_str = malloc(capacity * sizeof(char));
    if (!token_str) return NULL; // Handle allocation failure

    while (input[*i] && !is_whitespace(input[*i])) {
        if (input[*i] == '\'' || input[*i] == '"') {
            // If a quote is found, process the quoted content
            char quote_type = input[*i];
            (*i)++;  // Skip the opening quote
            while (input[*i] && input[*i] != quote_type) {
                token_str[j++] = input[*i];
                (*i)++;
            }
            (*i)++;  // Skip the closing quote
        } else {
            token_str[j++] = input[*i];
            (*i)++;
        }

        // Resize buffer if necessary
        if (j >= capacity) {
            capacity *= 2;
            char *new_str = realloc(token_str, capacity * sizeof(char));
            if (!new_str) {
                free(token_str);
                return NULL; // Handle allocation failure
            }
            token_str = new_str;
        }
    }

    token_str[j] = '\0';

    t_token *token = create_token(token_str, WORD);
    free(token_str);
    return token;
}
