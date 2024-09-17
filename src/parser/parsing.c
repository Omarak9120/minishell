/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksayour <ksayour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:56:28 by oabdelka          #+#    #+#             */
/*   Updated: 2024/09/16 22:08:23 by ksayour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Utility function to count the number of arguments for a command
int count_args(t_token *token)
{
    int count = 0;
    while (token && token->type == WORD)
    {
        count++;
        token = token->next;
    }
    return count;
}

// Function to create a new command node
t_command *create_command()
{
    t_command *cmd = (t_command *)malloc(sizeof(t_command));
    if (!cmd)
        return NULL;
    cmd->command = NULL;
    cmd->args = NULL;
    cmd->pipe_fd[0] = -1;
    cmd->pipe_fd[1] = -1;
    cmd->in_fd = 0;  // default to stdin
    cmd->out_fd = 1; // default to stdout
    cmd->next = NULL;
    return cmd;
}

// Function to parse the token linked list and create a command linked list
t_command *parse_tokens(t_token *tokens)
{
    t_command *cmd_list = NULL;
    t_command *current_cmd = NULL;
    t_token *cur_token = tokens;

    while (cur_token)
    {
        // Create a new command structure when encountering a WORD token
        if (cur_token->type == WORD)
        {
            t_command *new_cmd = create_command();
            if (!cmd_list)
                cmd_list = new_cmd;
            else
                current_cmd->next = new_cmd;
            current_cmd = new_cmd;

            // Set the command and its arguments
            current_cmd->command = strdup(cur_token->str);

            int arg_count = count_args(cur_token);
            current_cmd->args = (char **)malloc((arg_count + 1) * sizeof(char *));
            int i = 0;
            while (cur_token && cur_token->type == WORD)
            {
                current_cmd->args[i] = strdup(cur_token->str);
                cur_token = cur_token->next;
                i++;
            }
            current_cmd->args[i] = NULL; // Null-terminate the args array
        }

        // Handle pipes
        if (cur_token && cur_token->type == PIPE)
        {
            if (pipe(current_cmd->pipe_fd) == -1)
            {
                perror("pipe");
                exit(EXIT_FAILURE);
            }
            current_cmd->out_fd = current_cmd->pipe_fd[1]; // Current command output goes to pipe
            cur_token = cur_token->next; // Move to the next token
        }

        // Handle redirections (input/output handling would be added here)
        // For now, we assume no redirection in this code
    }

    return cmd_list;
}

// Helper function to free the command list
void free_command_list(t_command *cmd_list)
{
    while (cmd_list)
    {
        t_command *tmp = cmd_list;
        cmd_list = cmd_list->next;
        free(tmp->command);
        for (int i = 0; tmp->args && tmp->args[i]; i++)
            free(tmp->args[i]);
        free(tmp->args);
        free(tmp);
    }
}

// // Example of how to use the parser
// int main()
// {
//     char    *str = "hello \"world\"";
//     // Create a sample token linked list: "ls | grep txt | sort"
//     t_token token1 = {"echo", WORD, NULL};
//     t_token token2 = {str, WORD, NULL};
//     // t_token token2 = {"|", PIPE, NULL};
//     // t_token token3 = {"|", PIPE, NULL};
//     // t_token token5 = {"|", PIPE, NULL};
//     // t_token token6 = {"sort", WORD, NULL};

//     token1.next = &token2;
//     // token2.next = &token3;
//     // token3.next = &token4;
//     // token4.next = &token5;
//     // token5.next = &token6;

//     // Parse the tokens into commands
//     t_command *cmd_list = parse_tokens(&token1);

//     // Print the parsed commands (for testing)
//     t_command *cur_cmd = cmd_list;
//     while (cur_cmd)
//     {
//         printf("Command: %s\n", cur_cmd->command);
//         for (int i = 0; cur_cmd->args[i]; i++)
//             printf("  Arg[%d]: %s\n", i, cur_cmd->args[i]);

//         printf("  in_fd: %d, out_fd: %d\n", cur_cmd->in_fd, cur_cmd->out_fd);
//         cur_cmd = cur_cmd->next;
//     }

//     // Free the command list
//     free_command_list(cmd_list);

//     return 0;
// }