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
                free_token_list(token_list);
                return NULL;
            }
            add_token(&token_list, token);
        }
        else if (input[i] == '\'') {
            t_token *token = create_quoted_token(input, &i, '\'');
            if (!token) {
                free_token_list(token_list);
                return NULL;
            }
            add_token(&token_list, token);
        }
        else {
            t_token *token = create_general_token(input, &i);
            if (!token) {
                free_token_list(token_list);
                return NULL;
            }
            add_token(&token_list, token);
        }
    }
    return token_list;
}

// Create a token for quoted strings (everything between quotes)
t_token *create_quoted_token(char *input, int *i, char quote_type) {
    char *quoted_str = NULL;  // Use dynamic allocation
    int capacity = 256;
    int j = 0;

    quoted_str = malloc(capacity * sizeof(char));
    if (!quoted_str) return NULL;

    (*i)++;  // Skip the opening quote

    // Read characters until the closing quote is found
    while (input[*i]) {
        if (input[*i] == quote_type) {
            // Closing quote found
            (*i)++;  // Skip the closing quote
            break;
        }

        // Handle escaped characters (e.g., \")
        if (input[*i] == '\\' && input[*i + 1] == quote_type) {
            quoted_str[j++] = input[*i + 1];  // Add the escaped character
            (*i) += 2;  // Skip the backslash and the escaped character
        } else {
            quoted_str[j++] = input[*i];  // Add the regular character
            (*i)++;
        }

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

    quoted_str[j] = '\0';  // Null-terminate the string

    // Check if the closing quote was found
    if (input[*i - 1] != quote_type) {
        printf("Syntax error: unmatched %c quote\n", quote_type);
        free(quoted_str);
        return NULL;  // Indicate an error by returning NULL
    }

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
        if (is_separator(input[*i])) {
            // If we have accumulated characters, break to create a WORD token
            if (j > 0) break;

            // Handle operator token
            int separator_length = is_double_separator(input, *i) ? 2 : 1;
            for (int k = 0; k < separator_length; k++) {
                token_str[j++] = input[*i];
                (*i)++;
            }
            token_str[j] = '\0';
            int token_type = get_token_type(token_str);
            t_token *token = create_token(token_str, token_type);
            free(token_str);
            return token;
        }
        else if (input[*i] == '\\' && input[*i + 1]) {
            (*i)++;  // Skip the backslash
            token_str[j++] = input[*i];  // Add the escaped character
            (*i)++;
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
