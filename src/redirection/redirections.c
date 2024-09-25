#include "../includes/minishell.h"

// Redirect output (>) to a file
void handle_output_redirection(char *file)
{
    printf("Redirecting output to file: %s\n", file);  // Debug print
    int fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        perror("dup2");
        close(fd);
        exit(EXIT_FAILURE);
    }
    close(fd);  // Close the file descriptor after redirection
}



// Append output (>>) to a file
void handle_append_redirection(char *file)
{
    printf("Trying to append to file: %s\n", file);  // Debugging print
    int fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        perror("dup2");
        exit(EXIT_FAILURE);
    }
    close(fd);
}

// Redirect input (<) from a file
void handle_input_redirection(char *file)
{
    printf("Trying to open file for input redirection: %s\n", file);  // Debugging print
    int fd = open(file, O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    if (dup2(fd, STDIN_FILENO) == -1)
    {
        perror("dup2");
        exit(EXIT_FAILURE);
    }
    close(fd);
}

// Handle heredoc (<<)
void handle_heredoc(char *delimiter)
{
    char *line;
    int pipefd[2];

    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        line = readline("> ");  // Read input from the user
        if (!line)
        {
            break;  // Handle Ctrl+D (EOF)
        }
        if (strcmp(line, delimiter) == 0)
        {
            free(line);
            break;
        }
        write(pipefd[1], line, strlen(line));
        write(pipefd[1], "\n", 1);  // Write to the pipe
        free(line);
    }

    close(pipefd[1]);
    if (dup2(pipefd[0], STDIN_FILENO) == -1)
    {
        perror("dup2");
        exit(EXIT_FAILURE);
    }
    close(pipefd[0]);
}


// Consolidated function to handle all redirection
void redirection_handle(t_command *cmd)
{
    for (int i = 0; cmd->args[i]; i++)
    {
        if (strcmp(cmd->args[i], ">") == 0)  // Output redirection
        {
            if (cmd->args[i + 1])
            {
                handle_output_redirection(cmd->args[i + 1]);
                cmd->args[i] = NULL;  // Remove redirection from arguments
                break;  // Stop processing further args after redirection
            }
            else
            {
                fprintf(stderr, "minishell: syntax error near `>`\n");
                return;
            }
        }
        else if (strcmp(cmd->args[i], ">>") == 0)  // Append redirection
        {
            if (cmd->args[i + 1])
            {
                handle_append_redirection(cmd->args[i + 1]);
                cmd->args[i] = NULL;  // Remove redirection from arguments
                break;  // Stop processing further args after redirection
            }
            else
            {
                fprintf(stderr, "minishell: syntax error near `>>`\n");
                return;
            }
        }
        else if (strcmp(cmd->args[i], "<") == 0)
        {
            if (cmd->args[i + 1])
            {
                handle_input_redirection(cmd->args[i + 1]);
                cmd->args[i] = NULL;
            }
            else
            {
                fprintf(stderr, "minishell: syntax error near `<`\n");
                return;
            }
        }
        else if (strcmp(cmd->args[i], "<<") == 0)
        {
            if (cmd->args[i + 1])
            {
                handle_heredoc(cmd->args[i + 1]);
                cmd->args[i] = NULL;
            }
            else
            {
                fprintf(stderr, "minishell: syntax error near `<<`\n");
                return;
            }
        }
    }
}

