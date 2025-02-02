/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:55:08 by oabdelka          #+#    #+#             */
/*   Updated: 2025/02/02 16:42:54 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/includes/libft.h"
# include "dictionary.h"
# include "trashman.h"
# include "trashman_env.h"

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
// # include <sys/types.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>

# define NULL_CHAR 666
// # define _POSIX_C_SOURCE 200809L

enum e_token_gender
{
	WORD,
	OPERATOR
};

enum e_token_specie
{
	UNDEFINED = -1,
	OUT_REDIRECT,
	APPEND,
	IN_REDIRECT,
	HERE_DOC,
	DOUBLE_QUOTE,
	SINGLE_QUOTE,
	PIPE
};

/*
dfa->value will hold the newly created token substring once we cut it.
dfa->size will track the total length of the string.
dfa->start is the index where the current token starts.
dfa->state is the current state of the DFA (0 means “starting state”).
dfa->quote is a flag indicating if we are inside quotes.
dfa->i is our current position in the input string.
*/
typedef struct s_dfa
{
	char	*value;
	int		size;
	int		start;
	int		state;
	int		quote;
	int		i;
}	t_dfa;

typedef struct s_token
{
	char					*token;
	enum e_token_gender		gender;
	enum e_token_specie		specie;
	int						was_quoted;
	int						was_squoted;
	struct s_token			*next;
	struct s_token			*prev;
}	t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_sub_token
{
	char				*content;
	struct s_sub_token	*next;
}				t_sub_token;

typedef struct s_cmd
{
	int				input_fd;
	int				output_fd;
	int				read_pipe;
	int				write_pipe;
	int				nbr_of_words;
	char			**cmd_exec;
	char			*cmd_path;
	int				pid;
	struct s_cmd	*next;
}		t_cmd;

typedef struct s_mini
{
	char				*path;
	t_list				*lst_memory;
	int					status;
	char				*cmd_line;
	char				*pathname;
	t_token				*token_list;
	t_token				**commands;
	t_dict				*env_list;
	t_cmd				*cmd_exec_list;
	int					syntax_error;
	char				**mini_environ;
	int					hd_file_index;
	struct sigaction	int_action;
	struct sigaction	quit_action;
}				t_mini;

// 00_utils.c omar
void		ctrl_d_exit(void);
t_mini		*get_address(void);

// 01_prompt.c
void		mini_prompt(t_mini *mini);

// 01_utils.c
void		mini_init(t_mini *pipex);
void		mini_trashman_collector(t_list **list_memory, void *trash);
// void		mini_safe_exit(t_mini *mini);

// 02_ctrl_signal.c
void		ctrl_signal(t_mini *mini);
void		sig_handler(int signum);
void		sig_handler_heredoc(int signum);

// 03_process_envp.c
// void	mini_process_envp(t_mini *pipex, char *envp[]);
void		mini_execute(t_mini *mini);

// 03_utils
char		*mini_get_path(char *envp[]);
void		free_heap(t_list *lst_memory);
void		mini_free_split(char **split);
char		*mini_whereis(char *cmd, char *path);
void		mini_trashman(t_list **lst_memory);

// 04_special_parameter.c
void		mini_special_parameter(t_mini *mini);
char		*mini_expand(char c, t_mini *mini);
int			ft_get_exit_status(int exit_status);

// 05_tokenizer.c
void		mini_tokenizer(t_mini *mini);
void		mini_init_dfa(t_dfa *dfa);
void		mini_automaton(t_mini *mini, t_dfa *dfa);
int			mini_get_next_state(int state, int column);
int			mini_get_column(char c);

// 05_utils_1.c
int			mini_is_end_state(int num);
void		mini_syntonize_index(t_dfa *dfa);
int			mini_is_back_state(int num);
int			mini_is_quote_state(int num);
int			mini_is_error_state(int num);

// 05_utils_2.c
void		mini_print_sintax_error_message(int state);
void		mini_cut_string(t_mini *mini, t_dfa *dfa);
void		mini_set_syntax_error(t_mini *mini);

void		mini_check_sintax(t_mini *mini, t_token *token_list);
void		mini_check_consecutive_op_sintax(t_mini *mini, t_token *token_list);
void		mini_check_pipe_space_pipe_sintax(t_mini *mini, \
t_token *token_list);

// 05_utils_3.c
t_token		*mini_token_lstnew(void *token, int state);
void		mini_get_token_gender(int state, t_token *token);
void		mini_get_token_specie(int state, t_token *token);
void		mini_token_lstadd_back(t_token **lst, t_token *new);
t_token		*mini_lstlast(t_token *lst);

// 05_utils_4.c
void		mini_free_token_list(t_token **lst_memory);
void		mini_lstdelone(t_token *lst);
void		debug_print_split(char **str); // FOR DEBUG ONLY
void		debug_print_list(t_token **head); // FOR DEBUG ONLY

// 05_utils_5.c
int			mini_was_quoted(int state);
int			mini_was_squoted(int state);
void		mini_handle_export_arg(t_mini *mini);

// 05_utils_6.c
void		mini_check_sintax(t_mini *mini, t_token *token_list);

// 05_utils_7.c
void		mini_init_hd_signal(t_mini *mini,
				int *stdin_backup, int *stdout_backup);
void		mini_finish_hd_signal(int *stdin_backup, int *stdout_backup);

// 06_parser.c
void		mini_parser(t_mini *mini);
void		mini_fill_cmd_array(t_mini *mini);
int			mini_count_nbr_pipes(t_token *token_list);
t_token		*mini_t_token_dup(t_token *t);

// 06_utils.c
void		debug_print_parse_list(t_token **head); // FOR DEBUG ONLY
void		debug_print_array_list(t_mini *mini); // FOR DEBUG ONLY

// 07_expansion.c
void		mini_expansion(t_mini *mini);
void		mini_token_expansion(t_mini *mini, int i);
char		*mini_sep_exp_join(t_mini *mini, char *token);
char		*mini_search_and_replace(t_mini *mini, char *sub_token);
char		*mini_get_dollar_sign(t_mini *mini, char *sub_token);
int			mini_has_invalid_char(char *sub_token);
char		*mini_expand_with_invalid(t_mini *mini, char *sub_token);
int			mini_is_invalid_char(char c);
char		*mini_str_after_invalid_char(char *sub_token);
char		*mini_str_before_invalid_char(char *sub_token);
char		*ft_strjoin_expansion(char const *s1, char const *s2);

// 07_utils_1.c
void		mini_getenv(t_mini *mini);
int			mini_strchr_index(char *str, char c);
char		*mini_sub_token_join(t_sub_token *sub_token_lst);

// 07_utils_2.c
void		mini_sub_tokenizier(char *str, \
t_sub_token **sub_token_lst, int start, int state);
int			mini_exp_get_next_state(int state, int column);
int			mini_exp_get_column(char c);
int			is_one_back_state(int state);
int			is_two_back_state(int state);

// 07_utils_3.c
t_sub_token	*mini_sub_token_lstnew(char *content);
t_sub_token	*mini_sub_token_lstlast(t_sub_token *lst);
void		mini_sub_token_lstadd_back(t_sub_token **lst, t_sub_token *new);

// 08_redirect.c
void		mini_redirect(t_mini *mini);
void		mini_find_redirect(t_mini *mini, int i);
void		mini_handle_out_redir(t_cmd *cmd_node, char *file);
void		mini_handle_in_redir(t_cmd *cmd_node, char *file);
void		mini_handle_append_redir(t_cmd *cmd_node, char *file);
void		mini_handle_heredoc_redir(t_cmd *redir_node, char *file);

// 08_utils_1.c
t_cmd		*mini_redir_lstnew(void);
void		mini_redir_lstadd_back(t_cmd **lst, t_cmd *new);
t_cmd		*mini_redir_lstlast(t_cmd *lst);

// 09_execute.c
void		mini_execute(t_mini *mini);
void		mini_build_cmd_exec(t_mini *mini);
void		mini_count_cmd_exec_words(t_token *token_node, \
t_cmd *cmd_exec_node);
void		mini_unite_cmd_exec_words(t_token *token_node, \
t_cmd *cmd_exec_node);
void		mini_match_cmd_exec_word(char *token, t_cmd *cmd_exec_node, int i);

// 10_get_cmd_path.c
void		mini_get_cmd_exec_path(t_mini *mini);
char		*mini_get_cmd_path(t_mini *mini, t_cmd *cmd_exec_node);
char		*mini_search_in_envlist(t_mini *mini, char *key);

// 11_open_pipes.c
void		mini_open_pipes(t_mini *mini);

// 12_mini_execve.c
void		mini_execve(t_mini *mini);
void		mini_exec_fork(t_mini *mini,
				t_cmd *cmd_exec_node, t_token *token_node);
void		mini_execve_child(t_mini *mini,
				t_cmd *cmd_exec_node, t_token *token_node);
void		mini_wait_childs(t_mini *mini);
void		mini_get_status(t_mini *mini, int status);

// 12_utils_1.c
void		mini_manage_execve_fd(t_cmd *cmd_exec_node);
void		mini_exit_if_fd_neg(t_cmd *cmd_exec_node);
void		command_not_found_handler(t_mini *mini, t_cmd *cmd_exec_node);
void		get_captalized_errors(t_mini *mini, t_cmd *cmd_exec_node);

// 12_utils_2.c
void		mini_close_all_fd(t_mini *mini);
void		mini_close_node_fd(t_cmd *cmd_exec_node);
void		mini_close_pipe_node_fd(t_cmd *cmd_exec_node);
void		mini_close_pipes(t_mini *mini, t_cmd *current);

// 12_utils_3.c
void		mini_exec_builtin(t_token *token_lst,
				t_mini *mini, t_cmd *cmd_exec_node);
int			mini_is_simple_cmd(t_cmd *cmd_exec_node);
t_token		*mini_exec_interface(char **cmd_exec);
int			mini_is_builtin(t_token *token_lst);
int			mini_is_builtin(t_token *token_lst);
int			mini_cmd_selection(t_token *token_lst, t_mini *mini);

// 12_utils_4.c
void		mini_call_to_builtin(t_mini *mini, char *cmd, t_token *arg);
void		mini_backup_builtin_stdin(int *stdin_backup, int *stdout_backup);
void		mini_set_builtin_fd(t_cmd *cmd_exec_node);
void		mini_restore_builtin_fd(int *stdin_backup, int *stdout_backup);

// 13_mini_remake_environ.c
void		mini_remake_environ(t_mini *mini);

// 14_split_expansion.c
// void		mini_split_expansion_in_nodes(t_mini *mini);
void		mini_find_space(t_mini *mini, int i);

// 15_heredoc.c
int			mini_is_valid_heredoc(t_token *token_node);
void		mini_handle_heredoc(t_mini *mini, t_token *token_node);

// 15_utils.c
char		*mini_hd_expansion(char *line);

// 95_builtin_cd.c
int			mini_cd(t_token *arg, t_dict **env_list);

// 97_builtin_unset.c
int			mini_unset(t_token *arg, t_dict **env_list);

// 97_utils_1.c
int			mini_valid_identifier(char *str, int state);

// 98_builtin_export.c
int			mini_export(t_token *arg, t_dict **env_list);

// 98_utils_1.c
int			mini_env_identifier(char *str, t_dict **env_list, \
int start, int state);
int			mini_env_get_next_state(int state, int column);
int			mini_env_get_column(char c);

// 99_builtin_echo.c
int			mini_echo(t_token *arg);
int			mini_add_new_line(char *str);

#endif
