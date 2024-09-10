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
*								MACROS										  *
******************************************************************************/

# define PROMPT "\001\e[45m\002>>> \001\e[0m\e[33m\002 Minishell>$ \001\e[0m\002"
# define CMD_NOT_FOUND 127
# define CMD_NOT_EXECUTABLE 126
# define FAILURE 1
# define SUCCESS 0

/******************************************************************************
*								STRUCTS										  *
******************************************************************************/

typedef enum e_token_type
{
    WORD = 1,
    PIPE,
    REDIRECT,
    // Add more token types as needed
    INPUT,
    TRUNC,
    HEREDOC,
    APPEND,
    END
} t_token_type;


// Token structure for storing parsed tokens (could be words, symbols, etc.)
typedef struct s_token
{
	char			*str;
	int				type;           // WORD, PIPE, REDIRECT, etc.
	struct s_token	*next;
}					t_token;

// Command structure that contains info about commands and I/O redirection
typedef struct s_command
{
	char			*command;
	char			**args;         // Arguments for the command
	int				pipe_fd[2];     // Pipe file descriptors
	int				in_fd;          // Input file descriptor
	int				out_fd;         // Output file descriptor
	struct s_command *next;
}					t_command;

// Data structure to hold all shell-related info
typedef struct s_data
{
	char			**env;          // Environment variables
	t_command		*cmd_list;      // List of commands to execute
	t_token			*token_list;    // List of tokens from user input
	char			*user_input;    // User input
}					t_data;

/******************************************************************************
*								FUNCTIONS									  *
******************************************************************************/

/* ------------------------ MAIN FUNCTIONS ----------------------------------*/

// minishell.c
void		init_shell(t_data *data, char **env);
void		run_shell(t_data *data);
void		exit_shell(t_data *data, int exit_code);

/* ------------------------ LEXER -----------------------------------------*/

// lexer.c
t_token		*tokenize_input(char *input);
void		free_token_list(t_token *token_list);

/* ------------------------ PARSER -----------------------------------------*/

// parser.c
t_command	*parse_tokens(t_token *tokens);
void		free_command_list(t_command *cmd_list);

/* ------------------------ EXECUTION -------------------------------------*/

// exec_cmd.c
void		execute_commands(t_data *data);
void		execute_builtin(t_command *cmd, t_data *data);
int			execute_binary(t_command *cmd, t_data *data);

/* ------------------------ SIGNALS ---------------------------------------*/

// signals.c
void		setup_signals(void);

/* ------------------------ BUILTINS --------------------------------------*/

// cd.c
int			builtin_cd(t_data *data, char **args);
// echo.c
int			builtin_echo(t_data *data, char **args);

/* ------------------------ UTILS -----------------------------------------*/

// error.c
void		print_error(char *msg, int exit_code);
// memory.c
void		free_data(t_data *data);

#endif
