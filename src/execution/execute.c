/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksayour <ksayour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:43:38 by ksayour           #+#    #+#             */
/*   Updated: 2024/09/17 14:53:51 by ksayour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Declaration of is_builtin before usage
int is_builtin(t_command *cmd);

// Execute a single command (builtin or external)
int execute_single_command(t_command *cmd, t_data *data) {
    if (is_builtin(cmd)) {
        return execute_builtin(cmd, data);
    } else {
        return execute_binary(cmd, data);
    }
}

// Check if the command is a built-in
int is_builtin(t_command *cmd) {
    if (strcmp(cmd->command, "cd") == 0 || strcmp(cmd->command, "echo") == 0 || 
        strcmp(cmd->command, "exit") == 0 || strcmp(cmd->command, "pwd") == 0 || 
        strcmp(cmd->command, "export") == 0 || strcmp(cmd->command, "unset") == 0 || 
        strcmp(cmd->command, "env") == 0) {
        return 1;
    }
    return 0;
}

// Execute built-in command
int execute_builtin(t_command *cmd, t_data *data) {
    if (strcmp(cmd->command, "cd") == 0) {
        return builtin_cd(data, cmd->args);
    } else if (strcmp(cmd->command, "echo") == 0) {
        return builtin_echo(data, cmd->args);
    } else if (strcmp(cmd->command, "pwd") == 0) {
        return builtin_pwd(data, cmd->args);
    } else if (strcmp(cmd->command, "export") == 0) {
        return builtin_export(data, cmd->args);
    } else if (strcmp(cmd->command, "unset") == 0) {
        return builtin_unset(data, cmd->args);
    } else if (strcmp(cmd->command, "env") == 0) {
        return builtin_env(data, cmd->args);
    } else if (strcmp(cmd->command, "exit") == 0) {
        return builtin_exit(data, cmd->args);
    }
    
    // If the command is not recognized, return a command not found status
    return CMD_NOT_FOUND;
}

// Execute external binaries
int execute_binary(t_command *cmd, t_data *data) {
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0) {
        // Child process
        if (execve(cmd->command, cmd->args, data->env) == -1) {
            print_error("Command execution failed", CMD_NOT_FOUND);
            exit(EXIT_FAILURE);
        }
    } else if (pid < 0) {
        // Fork failed
        print_error("Fork failed", FAILURE);
    } else {
        // Parent process waits for the child to finish
        waitpid(pid, &status, 0);
    }
    return SUCCESS;
}

// Execute piped commands
int execute_piped_commands(t_command *cmd, t_data *data) {
    int pipe_fd[2];
    int prev_fd = -1;  // Used to store the previous read end of the pipe
    pid_t pid;
    int status;

    while (cmd) {
        // Create a pipe if there's another command after the current one
        if (cmd->next) {
            if (pipe(pipe_fd) == -1) {
                perror("Pipe error");
                return FAILURE;
            }
        }

        pid = fork();
        if (pid == 0) {  // Child process
            // If it's not the first command, redirect input from the previous pipe
            if (prev_fd != -1) {
                dup2(prev_fd, STDIN_FILENO);
                close(prev_fd);
            }
            // If there's another command, redirect output to the current pipe
            if (cmd->next) {
                close(pipe_fd[0]);  // Close the read end of the current pipe
                dup2(pipe_fd[1], STDOUT_FILENO);
                close(pipe_fd[1]);
            }

            // Execute the command (builtin or binary)
            if (is_builtin(cmd)) {
                exit(execute_builtin(cmd, data));
            } else {
                if (execve(cmd->command, cmd->args, data->env) == -1) {
                    perror("minishell");
                    exit(EXIT_FAILURE);
                }
            }
        } else if (pid < 0) {
            perror("Fork error");
            return FAILURE;
        }

        // Parent process: close the write end of the current pipe and store the read end
        if (cmd->next) {
            close(pipe_fd[1]);
            prev_fd = pipe_fd[0];
        }

        // Move to the next command in the chain
        cmd = cmd->next;
    }

    // Parent process waits for all child processes to finish
    while (wait(&status) > 0);
    return SUCCESS;
}

// Handle redirection
int handle_redirection(t_command *cmd) {
    if (cmd->in_fd != STDIN_FILENO) {
        dup2(cmd->in_fd, STDIN_FILENO);  // Redirect input
        close(cmd->in_fd);  // Close file descriptor after duplication
    }

    if (cmd->out_fd != STDOUT_FILENO) {
        dup2(cmd->out_fd, STDOUT_FILENO);  // Redirect output
        close(cmd->out_fd);  // Close file descriptor after duplication
    }
    return SUCCESS;
}

// Execute commands with or without pipes
void execute_commands(t_data *data) {
    t_command *cmd = data->cmd_list;

    // If there's a pipe between commands, handle them as a piped sequence
    if (cmd && cmd->next) {
        execute_piped_commands(cmd, data);
    } else {
        // If there's no pipe, execute commands normally
        while (cmd) {
            handle_redirection(cmd);  // Handle any redirections
            execute_single_command(cmd, data);
            cmd = cmd->next;
        }
    }
}
