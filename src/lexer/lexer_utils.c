#include "minishell.h"

// Check if character is whitespace
int is_whitespace(char c) {
    return (c == ' ' || c == '\t' || c == '\n');
}

// Check if character is a shell separator (pipe, redirect, etc.)
int is_separator(char c) {
    return (c == '|' || c == '>' || c == '<');
}
