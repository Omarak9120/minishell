/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksayour <ksayour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:56:30 by oabdelka          #+#    #+#             */
/*   Updated: 2024/09/14 17:18:45 by ksayour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"


void execute(char **args) {
    pid_t pid = fork();
    
    if (pid == 0) {  // Child process
        if (execve(args[0], args, NULL) == -1) {
            perror("minishell");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {  // Fork failed
        perror("minishell");
    } else {  // Parent process
        waitpid(pid, NULL, 0);
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
        return builtin_echo(cmd->args);
    } else if (strcmp(cmd->command, "pwd") == 0) {
        return builtin_pwd();
    } else if (strcmp(cmd->command, "export") == 0) {
        return builtin_export(data, cmd->args);
    } else if (strcmp(cmd->command, "unset") == 0) {
        return builtin_unset(data, cmd->args);
    } else if (strcmp(cmd->command, "env") == 0) {
        return builtin_env(data);
    } else if (strcmp(cmd->command, "exit") == 0) {
        return builtin_exit(data, cmd->args);
    }
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

// Execute commands with piping
int execute_with_pipe(t_command *cmd, t_data *data) {
    int pipe_fd[2];
    pid_t pid1, pid2;

    pipe(pipe_fd);

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

    close(pipe_fd[0]);
    close(pipe_fd[1]);

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    return SUCCESS;
}

// Execute the command
void execute_commands(t_data *data) {
    t_command *cmd = data->cmd_list;

    while (cmd) {
        if (is_builtin(cmd)) {
            execute_builtin(cmd, data);
        } else {
            execute_binary(cmd, data);
        }
        cmd = cmd->next;
    }
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
