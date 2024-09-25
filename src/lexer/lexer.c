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
        // Check for redirection operators
        else if (input[i] == '>' || input[i] == '<') {
            if (input[i + 1] == input[i]) {  // Handle cases like '>>' or '<<'
                t_token *token = create_separator_token(input, &i, 2); // Double char tokens
                add_token(&token_list, token);
            } else {
                t_token *token = create_separator_token(input, &i, 1); // Single char tokens
                add_token(&token_list, token);
            }
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

t_token *create_separator_token(char *input, int *i, int num_chars) {
    t_token *new_token = malloc(sizeof(t_token));
    if (!new_token)
        return NULL;

    // Allocate memory for the token string based on num_chars (1 or 2)
    new_token->str = malloc((num_chars + 1) * sizeof(char));
    if (!new_token->str) {
        free(new_token);
        return NULL;
    }

    // Copy the separator characters from the input string to the token string
    strncpy(new_token->str, &input[*i], num_chars);
    new_token->str[num_chars] = '\0';  // Null-terminate the token string

    // Set token type based on the separator
    if (strcmp(new_token->str, ">") == 0)
        new_token->type = REDIRECT_OUT;
    else if (strcmp(new_token->str, ">>") == 0)
        new_token->type = APPEND;
    else if (strcmp(new_token->str, "<") == 0)
        new_token->type = REDIRECT_IN;
    else if (strcmp(new_token->str, "<<") == 0)
        new_token->type = HEREDOC;
    else
        new_token->type = INVALID;  // Set an invalid type for unknown tokens

    *i += num_chars;  // Move the index forward by the number of characters processed
    new_token->next = NULL;
    return new_token;
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
        // Check for special tokens
        if (input[*i] == '>' || input[*i] == '<' || input[*i] == '|') {
            // If we encounter a special character, create a token and return
            char special_char[3] = {input[*i], '\0', '\0'};

            // Check for double-character tokens like ">>" or "<<"
            if ((input[*i] == '>' && input[*i + 1] == '>') || (input[*i] == '<' && input[*i + 1] == '<')) {
                special_char[1] = input[*i + 1];
                (*i)++;
            }

            (*i)++; // Move to the next character after the special character(s)
            return create_token(special_char, get_token_type(special_char));
        }

        // Handle quoted content
        if (input[*i] == '\'' || input[*i] == '"') {
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

    // Create token for regular words
    t_token *token = create_token(token_str, WORD);
    free(token_str);
    return token;
}