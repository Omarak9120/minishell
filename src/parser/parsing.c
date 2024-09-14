/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksayour <ksayour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:56:28 by oabdelka          #+#    #+#             */
/*   Updated: 2024/09/14 16:55:08 by ksayour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"


char **parse(char *input) {
    char **tokens = malloc(sizeof(char*) * 64);  // Example size
    char *token = strtok(input, " ");
    int i = 0;

    while (token) {
        tokens[i++] = token;
        token = strtok(NULL, " ");
    }
    tokens[i] = NULL;
    return tokens;
}

int is_builtin(t_command *cmd) {
    if (strcmp(cmd->command, "cd") == 0 || strcmp(cmd->command, "echo") == 0 || 
        strcmp(cmd->command, "exit") == 0 || strcmp(cmd->command, "pwd") == 0) {
        return 1;
    }
    return 0;
}

int execute_binary(t_command *cmd, t_data *data) {
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0) {
        // This is the child process
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

int execute_with_pipe(t_command *cmd, t_data *data) {
    int pipe_fd[2];
    pid_t pid1, pid2;

    pipe(pipe_fd);  // Create the pipe

    pid1 = fork();
    if (pid1 == 0) {
        // First child process
        dup2(pipe_fd[1], STDOUT_FILENO);  // Redirect stdout to pipe
        close(pipe_fd[0]);  // Close read end of the pipe
        execve(cmd->command, cmd->args, data->env);
    }

    pid2 = fork();
    if (pid2 == 0) {
        // Second child process
        dup2(pipe_fd[0], STDIN_FILENO);  // Redirect stdin to pipe
        close(pipe_fd[1]);  // Close write end of the pipe
        execve(cmd->next->command, cmd->next->args, data->env);
    }

    // Parent closes both ends of the pipe
    close(pipe_fd[0]);
    close(pipe_fd[1]);

    // Parent waits for both child processes to finish
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    return SUCCESS;
}

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

int builtin_cd(t_data *data, char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "cd: expected argument\n");
    } else {
        if (chdir(args[1]) != 0) {
            perror("cd");
        }
    }
    return SUCCESS;
}

void execute_commands(t_data *data) {
    t_command *cmd = data->cmd_list;

    while (cmd) {
        if (is_builtin(cmd)) {
            execute_builtin(cmd, data);
        } else {
            // Fork and execute external binaries
            execute_binary(cmd, data);
        }
        cmd = cmd->next;
    }
}
