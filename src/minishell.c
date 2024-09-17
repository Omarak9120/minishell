#include "../includes/minishell.h"

int main() {
    char *input;

    signal(SIGINT, handle_sigint);   // Ctrl + C
    signal(SIGQUIT, SIG_IGN);        // Ignore Ctrl + backslash

    while (1) {
        input = readline("minishell> ");
        if (!input)
            break;  // Handle EOF (Ctrl+D)
        
        if (input[0] != '\0')
            add_history(input);  // Add input to history

        t_token *token_list = tokenize_input(input);
	    t_command *cmd_list = parse_tokens(token_list);

        t_command *cur_cmd = cmd_list;
		while (cur_cmd)
		{
			printf("Command: %s\n", cur_cmd->command);
			for (int i = 0; cur_cmd->args[i]; i++)
				printf("  Arg[%d]: %s\n", i, cur_cmd->args[i]);

			printf("  in_fd: %d, out_fd: %d\n", cur_cmd->in_fd, cur_cmd->out_fd);
			cur_cmd = cur_cmd->next;
		}
    }
    return 0;
}