/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   09_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:51:29 by oabdelka          #+#    #+#             */
/*   Updated: 2025/02/03 13:54:14 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
/**
 *
 * 1) Build cmd_exec:
 *    Convert your parsed tokens into arrays of strings 
 *    (e.g. cmd_exec = {"/bin/echo", "hello", NULL}).
 *
 * 2) Get cmd_exec_path:
 *    Find the path to each command (e.g. /bin/echo).
 *
 * 3) Open pipes:
 *    If you have multiple commands in a pipeline, set up the necessary 
 *    pipe file descriptors.
 *
 * 4) Remake Environ:
 *    Rebuild mini->mini_environ from your env_list so execve 
 *    has the correct environment.
 *
 * 5) Execute:
 *    Fork and execve each command with its redirections, 
 *    environment, pipes, etc.
 */

void	execute(t_mini *mini)
{
	mini_build_cmd_exec(mini);
	mini_get_cmd_exec_path(mini);
	open_pipes(mini);
	mini_remake_environ(mini);
	mini_execve(mini);
}
/*
 *   Converts the parsed tokens for each command into an array of strings 
 *   (cmd_exec). Skips redirection operators and file names so the executable 
 *   only receives actual arguments.
 */

void	mini_build_cmd_exec(t_mini *mini)
{
	int		i;
	t_token	*token_node;
	t_cmd	*cmd_exec_node;

	i = 0;
	token_node = mini->commands[i];
	cmd_exec_node = mini->cmd_exec_list;
	while (token_node)
	{
		mini_count_cmd_exec_words(token_node, cmd_exec_node);
		if (cmd_exec_node->nbr_of_words)
			mini_unite_cmd_exec_words(token_node, cmd_exec_node);
		i++;
		token_node = mini->commands[i];
		cmd_exec_node = cmd_exec_node->next;
	}
}
/*
 *   Counts how many tokens for a given command are actual arguments (vs. 
 *   redirection symbols or files). This determines how large the cmd_exec 
 *   array should be.
 */

void	mini_count_cmd_exec_words(t_token *token_node, t_cmd *cmd_exec_node)
{
	int	i;

	i = 0;
	while (token_node)
	{
		if (token_node->specie == OUT_REDIRECT
			|| token_node->specie == IN_REDIRECT
			|| token_node->specie == APPEND
			|| token_node->specie == HERE_DOC)
		{
			token_node = token_node->next->next;
			continue ;
		}
		i++;
		token_node = token_node->next;
	}
	cmd_exec_node->nbr_of_words = i;
}
/**
 *   Allocates a char** for cmd_exec and fills it with each 
 *   non-redirection token. These tokens become the arguments that 
 *   will be passed to the executable (cmd_exec[0], cmd_exec[1], etc.).
 */

void	mini_unite_cmd_exec_words(t_token *token_node, t_cmd *cmd_exec_node)
{
	int		i;

	cmd_exec_node->cmd_exec = ft_calloc(sizeof(char *),
			cmd_exec_node->nbr_of_words + 1);
	ft_collect_mem(cmd_exec_node->cmd_exec);
	i = 0;
	while (token_node)
	{
		if (token_node->specie == OUT_REDIRECT
			|| token_node->specie == IN_REDIRECT
			|| token_node->specie == APPEND
			|| token_node->specie == HERE_DOC)
		{
			token_node = token_node->next->next;
			continue ;
		}
		if (token_node->token == NULL)
		{
			token_node = token_node->next;
			continue ;
		}
		mini_match_cmd_exec_word(token_node->token, cmd_exec_node, i);
		i++;
		token_node = token_node->next;
	}
}

void	mini_match_cmd_exec_word(char *token, t_cmd *cmd_exec_node, int i)
{
	char	*current_word;

	current_word = ft_strdup(token);
	ft_collect_mem(current_word);
	cmd_exec_node->cmd_exec[i] = current_word;
}

/*
echo hello world > out.txt

[Token #1] -> "echo" (WORD)
   next
[Token #2] -> "hello" (WORD)
   next
[Token #3] -> "world" (WORD)
   next
[Token #4] -> ">" (OPERATOR: OUT_REDIRECT)
   next
[Token #5] -> "out.txt" (WORD)
   next
NULL


mini->commands[0] -> token list for command 0
mini->commands[1] -> token list for command 1
mini->commands[2] -> token list for command 2
...

typedef struct s_cmd {
    int     input_fd;   -> 0 or a file descriptor
    int     output_fd;  -> 1 or a file descriptor
    char    **cmd_exec; -> e.g. ["echo", "hello", "world", NULL]
    char    *cmd_path;  -> e.g. "/bin/echo"
    struct s_cmd *next; -> pointer to next command in the pipeline
    ...
} t_cmd;


mini->cmd_exec_list -> [Cmd Node #1]
                        input_fd  = 0
                        output_fd = 3   (file descriptor pointing to "out.txt")
                        cmd_exec  = ["echo", "hello", "world", NULL]
                        cmd_path  = "/bin/echo"
                        next      = NULL


if we have | :

[Cmd Node #1] -- (next) --> [Cmd Node #2] -- (next) -->
[Cmd Node #3] -- (next) --> NULL

*/