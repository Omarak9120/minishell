#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>

/******************************************************************************
*                               MACROS                                         *
******************************************************************************/

# define PROMPT "\001\e[45m\002>>> \001\e[0m\e[33m\002 Minishell>$ \001\e[0m\002"
# define CMD_NOT_FOUND 127
# define CMD_NOT_EXECUTABLE 126
# define FAILURE 1
# define SUCCESS 0

/******************************************************************************
*                               STRUCTS                                        *
******************************************************************************/

typedef enum e_token_type
{
    WORD = 1,
    PIPE = 2,
    REDIRECT,
    REDIRECT_OUT = 3,
    REDIRECT_IN = 4,
    SEMICOLON,
    APPEND = 5,
    HEREDOC = 6,
    INVALID = 7,
    BUILTIN = 8,
    BACKGROUND,
    AND,
    OR,
    INPUT,
    TRUNC,
    END
} t_token_type;

// Token structure for storing parsed tokens (could be words, symbols, etc.)
typedef struct s_token
{
    char            *str;
    int             type;           // WORD, PIPE, REDIRECT, etc.
    struct s_token  *next;
}                   t_token;

// Command structure that contains info about commands and I/O redirection
typedef struct s_command
{
    char            *command;
    char            **args;         // Arguments for the command
    int             pipe_fd[2];     // Pipe file descriptors
    int             in_fd;          // Input file descriptor
    int             out_fd;         // Output file descriptor
    struct s_command *next;
}                   t_command;

// Data structure to hold all shell-related info
typedef struct s_data
{
    char            **env;          // Environment variables
    t_command       *cmd_list;      // List of commands to execute
    t_token         *token_list;    // List of tokens from user input
    char            *user_input;    // User input
}                   t_data;

/******************************************************************************
*                               FUNCTIONS                                     *
******************************************************************************/

/* ------------------------ MAIN FUNCTIONS ----------------------------------*/

// minishell.c
void        init_shell(t_data *data, char **env);
void        run_shell(t_data *data);
void        exit_shell(t_data *data, int exit_code);

/* ------------------------ LEXER -----------------------------------------*/

// lexer.c
t_token     *tokenize_input(char *input);  // Tokenize the input into tokens
void        free_token_list(t_token *token_list);  // Free token list

/* ------------------------ PARSER -----------------------------------------*/

// parser.c
t_command   *parse_tokens(t_token *tokens);  // Parse tokens into commands
void        free_command_list(t_command *cmd_list);  // Free command list

/* ------------------------ EXECUTION -------------------------------------*/

// exec_cmd.c
void        execute_commands(t_data *data);  // Execute the commands
void        execute_builtin(t_command *cmd, t_data *data);  // Execute built-in commands
int         execute_binary(t_command *cmd, t_data *data);  // Execute external binaries

/* ------------------------ SIGNALS ---------------------------------------*/

// signals.c
void        handle_sigint(int sig);
void        setup_signals(void);  // Setup signal handling

/* ------------------------ BUILTINS --------------------------------------*/
// Function prototypes for built-ins

// cd.c
int         builtin_cd(t_data *data, char **args);  // Built-in 'cd' command

// pwd.c
int         builtin_pwd(void);

// env.c
int         builtin_env(t_data *data);

// export.c
int         builtin_export(t_data *data, char **args);

// unset.c
int         builtin_unset(t_data *data, char **args);

// exit.c
int         builtin_exit(t_data *data, char **args);

/* ------------------------ UTILS -----------------------------------------*/

// error.c
void        print_error(char *msg, int exit_code);  // Print error messages

// memory.c
void        free_data(t_data *data);  // Free the shell data structure

/* ------------------------ TOKEN MANAGEMENT ------------------------------*/

// Token management functions
int         get_token_type(char *token);    // Determine token type
t_token     *create_token(char *str, int type);  // Create a new token
void        add_token(t_token **token_list, t_token *new_token);  // Add token to list
void        free_token_list(t_token *token_list);  // Free all tokens in the list
int         validate_tokens(t_token *token_list);  // Validate tokens for syntax correctness
t_token     *create_separator_token(char *input, int *i);
t_token     *create_word_token(char *input, int *i);
t_token     *create_quoted_token(char *input, int *i, char quote_type);
t_token     *create_escape_sequence(char *input, int *i);
int         is_valid_word(char *str);
int         is_builtin(char *str);
t_token     *create_word_with_separator(char *input, int *i);
t_token     *create_general_token(char *input, int *i);

/* ------------------------ TOKEN HELPERS ----------------------------------*/

// Helpers for tokenizing input
int         is_whitespace(char c);  // Check if character is a whitespace
int         is_separator(char c);   // Check if character is a separator (pipe, redirect, etc.)
int         is_double_separator(char *input, int i);  // Check for double-character separators

#endif
