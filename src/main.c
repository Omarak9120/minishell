#include "../includes/minishell.h"

int main() {
    char *input;
    t_data data;

    // Set up the shell environment
    setup_shell(&data);  // Initialize environment, signals, etc.
    ft_signal_setup_for_input();  // Setup signal handling for shell input

    while (1) {
        // Set up signal handling for user input (e.g., Ctrl+C at the prompt)
        ft_signal_setup_for_input();  // Ensure proper signal setup for input prompt

        // Read input from the user
        input = readline("minishell> ");
        
        // Handle EOF (Ctrl+D)
        if (!input) {
            printf("exit\n");
            break;
        }

        // If input is not empty, add it to history
        if (input[0] != '\0') {
            add_history(input);
        }

        // Tokenize the input
        t_token *token_list = tokenize_input(input);
        if (!token_list) {
            free(input);  // Free input memory
            continue;  // Skip if no valid tokens
        }

        // Parse tokens into a command list
        t_command *cmd_list = parse_tokens(token_list);
        if (!cmd_list) {
            free_token_list(token_list);  // Free token list if parsing failed
            free(input);
            continue;
        }

        // Handle redirection (if any)
        t_command *cmd = cmd_list;
        while (cmd) {
            redirection_handle(cmd);
            cmd = cmd->next;
        }

        // Reset signals to default for command execution
        ft_reset_signals();  // Signals should be reset to default before running commands

        // Execute commands
        data.cmd_list = cmd_list;
        execute_commands(&data);

        // Check for signals after command execution
        ft_check_signal(&data);  // Ensure signals are correctly processed

        // Clean up allocated memory
        free_command_list(cmd_list);
        free_token_list(token_list);
        free(input);  // Free input after processing
    }

    cleanup_shell(&data);  // Clean up shell resources on exit
    return 0;
}
