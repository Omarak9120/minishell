#include "../../includes/minishell.h"  // Ensure your token types are defined here
#include <string.h>  // Include for strdup if not using ft_strdup

// A simple test function to tokenize input, validate, and print tokens
int main(void)
{
    // Modifiable string for tokenization
    // char input[] = "echo \"hello world\" > file";
    // char input[] = "echo \"hello \\\"world\\\"\"";
    // char input[] = "echo \"hello world\" > output.txt";
    // char input[] = "ls | grep txt | sort";
    char input[] = "echo \"file contents\" > output.txt";



    // char input[] = "echo 'hello world' > file";
    // char *token;
    // t_token_type token_type;
    // t_token *token_list = NULL;  // Initialize the token list (linked list)

    // // Tokenize input using strtok (or another custom tokenizer)
    // token = strtok(input, " ");  // Tokenize by spaces

    // while (token != NULL)
    // {
    //     // Determine token type
    //     token_type = get_token_type(token);

    //     // Create a new token and add it to the linked list
    //     t_token *new_token = create_token(token, token_type);
    //     add_token(&token_list, new_token);

    //     // Get the next token
    //     token = strtok(NULL, " ");
    // }

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
        return REDIRECT_OUT;  // Output redirection
    else if (strcmp(str, "<") == 0)
        return REDIRECT_IN;   // Input redirection
    else if (strcmp(str, ">>") == 0)
        return APPEND;        // Append redirection
    else if (strcmp(str, "<<") == 0)
        return HEREDOC;       // Heredoc redirection
    else
        return WORD;          // Default type for commands/words
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


        // Move to the next token
        current = current->next;
    }

    // If no syntax errors, return success
    return SUCCESS;
}

// Main function to start the lexing process
t_token *tokenize_input(char *input) {
    t_token *token_list = NULL;
    int i = 0;

    while (input[i]) {
        if (is_whitespace(input[i])) {
            i++;  // Skip whitespaces
        }
        else if (input[i] == '"') {
            // Handle double quoted strings
            add_token(&token_list, create_quoted_token(input, &i, '"'));
        }
        else if (input[i] == '\'') {
            // Handle single quoted strings
            add_token(&token_list, create_quoted_token(input, &i, '\''));
        }
        else if (is_double_separator(input, i)) {
            add_token(&token_list, create_separator_token(input, &i));
            i++;  // Skip the second character of the double separator
        }
        else if (is_separator(input[i])) {
            add_token(&token_list, create_separator_token(input, &i));
        }
        else if (input[i] == '\\') {
            // Handle escape sequences
            add_token(&token_list, create_escape_sequence(input, &i));
        }
        else {
            add_token(&token_list, create_word_token(input, &i));
        }
    }
    return token_list;
}

t_token *create_word_token(char *input, int *i) {
    char word[256];  // Temporary buffer to hold the word
    int j = 0;

    // Loop through the input until we hit a separator or whitespace
    while (input[*i] && !is_whitespace(input[*i]) && !is_separator(input[*i])) {
        word[j++] = input[*i];
        (*i)++;
    }
    word[j] = '\0';  // Null-terminate the word string

    // Create and return a new token with the word string
    return create_token(word, WORD);
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

    (*i)++;  // Skip the closing quote

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

    return create_token(separator, PIPE);  // You may change PIPE to the correct type as needed
}
// Check if character is whitespace
int is_whitespace(char c) {
    return (c == ' ' || c == '\t' || c == '\n');
}

// Check if character is a shell separator (pipe, redirect, etc.)
int is_separator(char c) {
    return (c == '|' || c == '>' || c == '<' || c == '&' || c == '(' || c == ')');
}
