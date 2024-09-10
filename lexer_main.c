#include <stdio.h>
#include <string.h>
#include "minishell.h" // Ensure your token types are defined here

// A simple test function to tokenize input and print the token type
int main(void)
{
    char *input = "cat | ls > file";  // Test input
    char *token;
    t_token_type token_type;

    // Tokenize input using strtok (or another custom tokenizer)
    token = strtok(input, " "); // Tokenize by spaces

    while (token != NULL)
    {
        // Example of determining token type based on the token value
        if (strcmp(token, "|") == 0)
            token_type = PIPE;
        else if (strcmp(token, ">") == 0)
            token_type = REDIRECT;
        else
            token_type = WORD;

        // Print the token and its type
        printf("Token: %s, Type: %d\n", token, token_type);

        // Get the next token
        token = strtok(NULL, " ");
    }

    return 0;
}
