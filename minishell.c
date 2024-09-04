#include "minishell.h"

int main() {
    char *input;
    char **args;

    signal(SIGINT, handle_signal);  // Handle Ctrl+C

    while (1) {
        input = readline("minishell> ");
        if (!input)
            break;  // Handle EOF (Ctrl+D)
        
        if (input[0] != '\0')
            add_history(input);  // Add input to history

        args = parse(input);  // Parse the input into tokens
        
        if (args[0])
            execute(args);  // Execute the parsed command

        free(input);
        free(args);
    }
    return 0;
}
