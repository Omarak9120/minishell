#include "../includes/minishell.h"

int main() {
    char *input;
    t_data data;

    // Set up the shell environment
    setup_shell(&data);  // Initialize environment, signals, etc.

    art();  // Display shell art if necessary
    // signal(SIGINT, handle_sigint);   // Handle Ctrl + C
    // signal(SIGQUIT, SIG_IGN);        // Ignore Ctrl + backslash (SIGQUIT)
    ft_signal_incmd();
    while (1) {
        input = readline("minishell> ");
        if (!input) {
            // Handle EOF (Ctrl+D) or null input
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
            free(input);  // Free the input memory
            continue;  // Skip if no valid tokens
        }

        // Parse tokens into a command list
        t_command *cmd_list = parse_tokens(token_list);

        if (!cmd_list) {
            free_token_list(token_list);  // Free token list if parsing failed
            free(input);
            continue;
        }

        // Debugging: Print parsed command details (Optional)
        t_command *cur_cmd = cmd_list;
        while (cur_cmd) {
            printf("Command: %s\n", cur_cmd->command);
            for (int i = 0; cur_cmd->args[i]; i++)
                printf("  Arg[%d]: %s\n", i, cur_cmd->args[i]);

            printf("  in_fd: %d, out_fd: %d\n", cur_cmd->in_fd, cur_cmd->out_fd);
            cur_cmd = cur_cmd->next;
        }

        // Execute the commands (either with or without pipes)
        data.cmd_list = cmd_list;
        execute_commands(&data);

        // Clean up allocated memory
        free_command_list(cmd_list);
        free_token_list(token_list);
        free(input);  // Free input after processing
    }

    cleanup_shell(&data);  // Clean up shell resources on exit
    return 0;
}
