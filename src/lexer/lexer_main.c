/*

#include "../../includes/minishell.h"  // Ensure your token types are defined here
#include <string.h>  // Include for strdup if not using ft_strdup

// A simple test function to tokenize input, validate, and print tokens
int main(void)
{
    // Modifiable string for tokenization
    // char input[] = "echo \"hello world\" >> file";
    // char input[] = "echo \"hello \\\"world\\\"\"";
    // char input[] = "echo \"hello world\" > output.txt";
    // char input[] = " | grep txt || sort echo omar";
    // char input[] = "echo \"file contents\" > output.txt";
    // char input[] = " cat << output ???";
    // char input[] = "echo Hello\\ World";
    // char input[] = "echo \"Hello World";
    char input[] = "cat|cat|ls";

    // char input[] = "echo \"Unmatched quote";
    



    t_token *token_list = tokenize_input(input);

    // Validate the token list before printing tokens
    if (validate_tokens(token_list) == SUCCESS) {
        printf("Token list is valid.\n");
    } else {
        printf("Token list has syntax errors.\n");
    }

    // Now we can traverse and print the token list for testing
    t_token *current = token_list;
    while (current != NULL)
    {
        printf("Token: %s, Type: %d\n", current->str, current->type);
        current = current->next;
    }

    // Free the token list after use
    free_token_list(token_list);
    return 0;
}


// Function to determine token type
// Define token types
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
        else if (current->type == REDIRECT || current->type == REDIRECT_OUT || 
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

// Main function to start the lexing process
// Adjusted tokenize_input function
t_token *tokenize_input(char *input) {
    t_token *token_list = NULL;
    int i = 0;

    while (input[i]) {
        if (is_whitespace(input[i])) {
            i++;  // Skip whitespaces
        }
        else if (input[i] == '"') {
            add_token(&token_list, create_quoted_token(input, &i, '"'));
        }
        else if (input[i] == '\'') {
            add_token(&token_list, create_quoted_token(input, &i, '\''));
        }
        else {
            add_token(&token_list, create_general_token(input, &i));
        }
    }
    return token_list;
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


// New function to create a word token that includes the separator
t_token *create_word_with_separator(char *input, int *i) {
    char word[256];
    int j = 0;

    // Collect the separator first
    if (is_double_separator(input, *i)) {
        word[j++] = input[*i];
        word[j++] = input[*i + 1];
        *i += 2;
    } else {
        word[j++] = input[*i];
        (*i)++;
    }

    // Now collect the word that follows
    while (input[*i] && !is_whitespace(input[*i]) && !is_separator(input[*i])) {
        word[j++] = input[*i];
        (*i)++;
    }

    word[j] = '\0';  // Null-terminate the word string

    // Create and return a new token with the word string
    return create_token(word, WORD);
}


// Adjusted create_word_token function
t_token *create_word_token(char *input, int *i) {
    char *word = NULL;      // Use dynamic memory allocation
    int capacity = 256;
    int j = 0;

    word = malloc(capacity * sizeof(char));
    if (!word) return NULL; // Handle allocation failure

    while (input[*i] && !is_whitespace(input[*i])) {
        if (input[*i] == '\\' && input[*i + 1]) {
            (*i)++;  // Skip the backslash
            word[j++] = input[*i];  // Add the escaped character
            (*i)++;
        } else {
            word[j++] = input[*i];
            (*i)++;
        }

        // Resize buffer if necessary
        if (j >= capacity) {
            capacity *= 2;
            char *new_word = realloc(word, capacity * sizeof(char));
            if (!new_word) {
                free(word);
                return NULL; // Handle allocation failure
            }
            word = new_word;
        }
    }
    word[j] = '\0';  // Null-terminate the word string

    // Create and return a new token with the word string
    t_token *token = create_token(word, WORD);
    free(word);  // Free the temporary buffer
    return token;
}





// Create a token for quoted strings (everything between quotes)
t_token *create_quoted_token(char *input, int *i, char quote_type) {
    char quoted_str[256];  // Buffer to store the quoted string
    int j = 0;

    (*i)++;  // Skip the opening quote

    // Read characters until the closing quote is found
    while (input[*i] && input[*i] != quote_type) {
        // Handle escaped characters (e.g., \")
        if (input[*i] == '\\' && input[*i + 1] == quote_type) {
            quoted_str[j++] = input[*i + 1];  // Add the escaped character
            (*i) += 2;  // Skip the backslash and the escaped character
        } else {
            quoted_str[j++] = input[*i];  // Add the regular character
            (*i)++;
        }
    }

    quoted_str[j] = '\0';  // Null-terminate the string

    // Check if the closing quote is missing
    if (input[*i] != quote_type) {
        printf("Syntax error: unmatched %c quote\n", quote_type);
        return NULL;  // Indicate an error by returning NULL
    } else {
        (*i)++;  // Skip the closing quote
    }

    // Return a single token containing the entire quoted string
    return create_token(quoted_str, WORD);
}



// Handle escape sequences (e.g., "\ ")
t_token *create_escape_sequence(char *input, int *i) {
    char escaped_str[3];
    
    // Only process the next character after backslash
    escaped_str[0] = input[*i + 1];
    escaped_str[1] = '\0';  // Null-terminate
    (*i) += 2;  // Skip the backslash and the next character

    return create_token(escaped_str, WORD);  // Treat escape sequences as WORD tokens
}

/// Check if the next two characters form a double-character separator
int is_double_separator(char *input, int i) {
    return ((input[i] == '>' && input[i+1] == '>') ||
            (input[i] == '<' && input[i+1] == '<'));
}


t_token *create_separator_token(char *input, int *i) {
    char separator[3];  // Create space for two characters and a null terminator

    // Check for double-character separator
    if (is_double_separator(input, *i)) {
        separator[0] = input[*i];
        separator[1] = input[*i + 1];
        separator[2] = '\0';
        *i += 2;  // Move the index past the double separator
    } else {
        separator[0] = input[*i];
        separator[1] = '\0';
        (*i)++;  // Move the index past the single separator
    }

    int token_type = get_token_type(separator);

     return create_token(separator, token_type);  // 7asab el type
}
// Check if character is whitespace
int is_whitespace(char c) {
    return (c == ' ' || c == '\t' || c == '\n');
}

// Check if character is a shell separator (pipe, redirect, etc.)
int is_separator(char c) {
    return (c == '|' || c == '>' || c == '<' || c == '&' || c == '(' || c == ')');
}

*/