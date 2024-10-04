/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjamil <mjamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:43:38 by ksayour           #+#    #+#             */
/*   Updated: 2024/10/04 17:28:29 by mjamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../includes/minishell.h"

#include "../../includes/minishell.h"

// Declaration of is_builtin before usage
int is_builtin(t_command *cmd);

// Function to execute an external command using fork
// void execute_external_command(t_data *data, t_command *cmd)
// {
//     pid_t pid = fork();
//     if (pid == 0)
//     {
//         // Handling input/output redirection
//         if (cmd->in_fd != STDIN_FILENO)
//         {
//             dup2(cmd->in_fd, STDIN_FILENO);
//             close(cmd->in_fd);
//         }
//         if (cmd->out_fd != STDOUT_FILENO)
//         {
//             dup2(cmd->out_fd, STDOUT_FILENO);
//             close(cmd->out_fd);
//         }
//         if (execvp(cmd->args[0], cmd->args) == -1)
//         {
//             ft_perror("minishell");
//             exit(EXIT_FAILURE);
//         }
//     }
//     else if (pid > 0)
//     {
//         int status;
//         waitpid(pid, &status, 0);
//         data->exit_status = WEXITSTATUS(status);
//     }
//     else
//     {
//         perror("minishell: fork");
//     }
// }

int execute_single_command(t_command *cmd, t_data *data) {
    // Handle built-in commands in the current process
    if (is_builtin(cmd)) {
        return execute_builtin(cmd, data);  // Execute in the parent shell process
    }

    // Check if PATH is set
    char *path = my_getenv(data->env , "PATH");
    if (path == NULL || strlen(path) == 0) {
        fprintf(stderr, "%s: No such file or directory\n", cmd->args[0]);
        data->exit_status = 127;  // Set exit status for command not found
        return FAILURE;
    }

    // For external commands, fork a child process
    pid_t pid = fork();  // Create a child process

    if (pid == 0) {  // Child process
        // Reset signal handling to default in child process
        signal(SIGINT, SIG_DFL);   // Allow Ctrl+C to terminate the child process
        signal(SIGQUIT, SIG_DFL);  // Allow Ctrl+\ to terminate the child process

        // Handle input/output redirection (if any)
        if (cmd->in_fd != STDIN_FILENO) {
            dup2(cmd->in_fd, STDIN_FILENO);
            close(cmd->in_fd);
        }
        if (cmd->out_fd != STDOUT_FILENO) {
            dup2(cmd->out_fd, STDOUT_FILENO);
            close(cmd->out_fd);
        }

        // Check if the command can be found
        if (execvp(cmd->args[0], cmd->args) == -1) {
            // If execvp fails, print "command not found" and exit with 127
            fprintf(stderr, "%s: command not found\n", cmd->args[0]);
            exit(127);  
        }
    } 
    else if (pid > 0) {  // Parent process
        int status;

        // Ignore SIGINT in the parent while waiting for the child
        signal(SIGINT, SIG_IGN);

        // Wait for the child process to finish
        waitpid(pid, &status, 0);

        // Restore signal handling for SIGINT in the parent
        signal(SIGINT, ft_sigint_handler_beforecmd);  // Restore Ctrl+C handling

        // If the child was terminated by a signal (e.g., Ctrl+C)
        if (WIFSIGNALED(status)) {
            int sig = WTERMSIG(status);
            if (sig == SIGINT) {
                printf("\n");  // Print a newline when Ctrl+C is pressed
                data->exit_status = 130;  // Set shell's exit status for Ctrl+C
            }
        } else if (WIFEXITED(status)) {
            data->exit_status = WEXITSTATUS(status);
        }
    } 
    else {
        perror("fork");
        return FAILURE;
    }

    return SUCCESS;
}


// Check if the command is a built-in
int is_builtin(t_command *cmd)
{
    return (strcmp(cmd->command, "cd") == 0 || strcmp(cmd->command, "echo") == 0 || 
            strcmp(cmd->command, "exit") == 0 || strcmp(cmd->command, "pwd") == 0 || 
            strcmp(cmd->command, "export") == 0 || strcmp(cmd->command, "unset") == 0 || 
            strcmp(cmd->command, "env") == 0);
}


int execute_piped_commands(t_command *cmd, t_data *data)
{
    int pipe_fd[2];
    int prev_fd = -1;
    pid_t pid;
    int status;
    int first_process = 1;  // Track the first process in the pipeline

    while (cmd)
    {
        if (cmd->next)  // If there is a next command, create a pipe
        {
            if (pipe(pipe_fd) == -1)
            {
                perror("Pipe error");
                return FAILURE;
            }
        }

        pid = fork();  // Fork a new process
        if (pid == 0)  // Child process
        {
            ft_reset_signals();  // Reset signal handlers to default

            if (!first_process)  // If this is not the first command, set stdin to previous pipe's output
            {
                dup2(prev_fd, STDIN_FILENO);
                close(prev_fd);
            }

            if (cmd->next)  // If there is a next command, set stdout to pipe's input
            {
                close(pipe_fd[0]);
                dup2(pipe_fd[1], STDOUT_FILENO);
                close(pipe_fd[1]);
            }

            // Execute the command (builtin or external)
            if (is_builtin(cmd))
            {
                exit(execute_builtin(cmd, data));
            }
            else
            {
                if (execvp(cmd->args[0], cmd->args) == -1)
                {
                    perror("minishell");
                    exit(EXIT_FAILURE);
                }
            }
        }
        else if (pid < 0)  // Fork error
        {
            perror("Fork error");
            return FAILURE;
        }

        // Parent process: close pipe write end, save read end for the next iteration
        if (!first_process)
        {
            close(prev_fd);
        }
        if (cmd->next)
        {
            close(pipe_fd[1]);
            prev_fd = pipe_fd[0];  // Save the read end of the pipe for the next process
        }

        first_process = 0;
        cmd = cmd->next;
    }

    // Wait for all child processes to finish
    while (wait(&status) > 0)
        ;

    return SUCCESS;
}


// Place this in exec_cmd.c or similar
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

    return CMD_NOT_FOUND;  // If no built-in command is found
}


// Handle redirection
int handle_redirection(t_command *cmd)
{
    if (cmd->in_fd != STDIN_FILENO)
    {
        dup2(cmd->in_fd, STDIN_FILENO);
        close(cmd->in_fd);
    }

    if (cmd->out_fd != STDOUT_FILENO)
    {
        dup2(cmd->out_fd, STDOUT_FILENO);
        close(cmd->out_fd);
    }
    return SUCCESS;
}



// Execute commands with or without pipes
void execute_commands(t_data *data)
{
    t_command *cmd = data->cmd_list;

    if (cmd && cmd->next)
    {
        execute_piped_commands(cmd, data);
    }
    else
    {
        while (cmd)
        {
            redirection_handle(cmd);  // Handle redirection first
            execute_single_command(cmd, data);  // Then execute the command
            cmd = cmd->next;
        }
    }
}


// // Declaration of is_builtin before usage
// int is_builtin(t_command *cmd);
// void execute_external_command(t_data *data, t_command *cmd)
// {
//     pid_t pid = fork();
//     if (pid == 0)
//     {
//         if (cmd->in_fd != STDIN_FILENO)
//         {
//             dup2(cmd->in_fd, STDIN_FILENO);
//             close(cmd->in_fd);
//         }
//         if (cmd->out_fd != STDOUT_FILENO)
//         {
//             dup2(cmd->out_fd, STDOUT_FILENO);
//             close(cmd->out_fd);
//         }
//         if (execvp(cmd->args[0], cmd->args) == -1)
//         {
//             ft_perror("minishell");
//             exit(EXIT_FAILURE);
//         }
//     }
//     else if (pid > 0)
//     {
//         int status;
//         waitpid(pid, &status, 0);
//         data->exit_status = WEXITSTATUS(status);
//     }
//     else
//         perror("minishell: fork");
// }

// // Execute a single command (builtin or external)
// int execute_single_command(t_command *cmd, t_data *data) {
//     if (is_builtin(cmd)) {
//         return execute_builtin(cmd, data);
//     } else {
//         execute_external_command(data, cmd);
//     }
//     return(0);
// }

// // Check if the command is a built-in
// int is_builtin(t_command *cmd) {
//     if (strcmp(cmd->command, "cd") == 0 || strcmp(cmd->command, "echo") == 0 || 
//         strcmp(cmd->command, "exit") == 0 || strcmp(cmd->command, "pwd") == 0 || 
//         strcmp(cmd->command, "export") == 0 || strcmp(cmd->command, "unset") == 0 || 
//         strcmp(cmd->command, "env") == 0) {
//         return 1;
//     }
//     return 0;
// }

// // Execute built-in command
// int execute_builtin(t_command *cmd, t_data *data) {
//     if (strcmp(cmd->command, "cd") == 0) {
//         return builtin_cd(data, cmd->args);
//     } else if (strcmp(cmd->command, "echo") == 0) {
//         return builtin_echo(data, cmd->args);
//     } else if (strcmp(cmd->command, "pwd") == 0) {
//         return builtin_pwd(data, cmd->args);
//     } else if (strcmp(cmd->command, "export") == 0) {
//         return builtin_export(data, cmd->args);
//     } else if (strcmp(cmd->command, "unset") == 0) {
//         return builtin_unset(data, cmd->args);
//     } else if (strcmp(cmd->command, "env") == 0) {
//         return builtin_env(data, cmd->args);
//     } else if (strcmp(cmd->command, "exit") == 0) {
//         return builtin_exit(data, cmd->args);
//     }
    
//     // If the command is not recognized, return a command not found status
//     return CMD_NOT_FOUND;
// }

// // Execute external binaries
// int execute_binary(t_command *cmd, t_data *data) {
//     pid_t pid;
//     int status;

//     pid = fork();
//     if (pid == 0) {
//         // Child process
//         if (execve(cmd->command, cmd->args, data->env) == -1) {
//             print_error("Command execution failed", CMD_NOT_FOUND);
//             exit(EXIT_FAILURE);
//         }
//     } else if (pid < 0) {
//         // Fork failed
//         print_error("Fork failed", FAILURE);
//     } else {
//         // Parent process waits for the child to finish
//         waitpid(pid, &status, 0);
//     }
//     return SUCCESS;
// }

// // Execute piped commands
// int execute_piped_commands(t_command *cmd, t_data *data) {
//     int pipe_fd[2];
//     int prev_fd = -1;  // Used to store the previous read end of the pipe
//     pid_t pid;
//     int status;

//     while (cmd) {
//         // Create a pipe if there's another command after the current one
//         if (cmd->next) {
//             if (pipe(pipe_fd) == -1) {
//                 perror("Pipe error");
//                 return FAILURE;
//             }
//         }

//         pid = fork();
//         if (pid == 0) {  // Child process
//             // If it's not the first command, redirect input from the previous pipe
//             if (prev_fd != -1) {
//                 dup2(prev_fd, STDIN_FILENO);
//                 close(prev_fd);
//             }
//             // If there's another command, redirect output to the current pipe
//             if (cmd->next) {
//                 close(pipe_fd[0]);  // Close the read end of the current pipe
//                 dup2(pipe_fd[1], STDOUT_FILENO);
//                 close(pipe_fd[1]);
//             }

//             // Execute the command (builtin or binary)
//             if (is_builtin(cmd)) {
//                 exit(execute_builtin(cmd, data));
//             } else {
//                 if (execve(cmd->command, cmd->args, data->env) == -1) {
//                     perror("minishell");
//                     exit(EXIT_FAILURE);
//                 }
//             }
//         } else if (pid < 0) {
//             perror("Fork error");
//             return FAILURE;
//         }

//         // Parent process: close the write end of the current pipe and store the read end
//         if (cmd->next) {
//             close(pipe_fd[1]);
//             prev_fd = pipe_fd[0];
//         }

//         // Move to the next command in the chain
//         cmd = cmd->next;
//     }

//     // Parent process waits for all child processes to finish
//     while (wait(&status) > 0);
//     return SUCCESS;
// }

// // Handle redirection
// int handle_redirection(t_command *cmd) {
//     if (cmd->in_fd != STDIN_FILENO) {
//         dup2(cmd->in_fd, STDIN_FILENO);  // Redirect input
//         close(cmd->in_fd);  // Close file descriptor after duplication
//     }

//     if (cmd->out_fd != STDOUT_FILENO) {
//         dup2(cmd->out_fd, STDOUT_FILENO);  // Redirect output
//         close(cmd->out_fd);  // Close file descriptor after duplication
//     }
//     return SUCCESS;
// }

// // Execute commands with or without pipes
// void execute_commands(t_data *data) {
//     t_command *cmd = data->cmd_list;

//     // If there's a pipe between commands, handle them as a piped sequence
//     if (cmd && cmd->next) {
//         execute_piped_commands(cmd, data);
//     } else {
//         // If there's no pipe, execute commands normally
//         while (cmd) {
//             handle_redirection(cmd);  // Handle any redirections
//             execute_single_command(cmd, data);
//             cmd = cmd->next;
//         }
//     }
// }
