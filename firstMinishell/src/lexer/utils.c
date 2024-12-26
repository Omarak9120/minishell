#include "../../includes/minishell.h" 


// Check if character is whitespace
int is_whitespace(char c) {
    return (c == ' ' || c == '\t' || c == '\n');
}

// Check if character is a shell separator (pipe, redirect, etc.)
int is_separator(char c) {
    return (c == '|' || c == '>' || c == '<' || c == '&' || c == '(' || c == ')');
}

// Check if the next two characters form a double-character separator
int is_double_separator(char *input, int i) {
    return ((input[i] == '>' && input[i+1] == '>') ||
            (input[i] == '<' && input[i+1] == '<'));
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
