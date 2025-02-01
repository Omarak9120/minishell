/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   15_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:10:04 by oabdelka          #+#    #+#             */
/*   Updated: 2025/02/01 19:10:05 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int		mini_create_file(t_mini *mini, t_token *token_node);
static void		mini_handle_null_or_delimiter(char *line, char *word,
					int status, int hd_file_fd);
static int		mini_is_null_or_delimiter(char *line, char *word);

int	mini_is_valid_heredoc(t_token *token_node)
{
	if (token_node && token_node->gender == WORD)
		return (1);
	return (0);
}

void	mini_handle_heredoc(t_mini *mini, t_token *token_node)
{
	char	*line;
	char	*exp_line;
	char	*word;
	int		hd_file_fd;

	word = token_node->token;
	hd_file_fd = mini_create_file(mini, token_node);
	while (1)
	{
		line = readline("> ");
		if (mini_is_null_or_delimiter(line, word))
		{
			mini_handle_null_or_delimiter(line, word, mini->status, hd_file_fd);
			break ;
		}
		if (token_node->was_quoted)
			exp_line = line;
		else
			exp_line = mini_hd_expansion(line);
		ft_printf_fd(hd_file_fd, "%s\n", exp_line);
		free(line);
	}
}
/*ctrl+D or "EOF = EOF"*/
static int	mini_is_null_or_delimiter(char *line, char *word)
{
	if (line == NULL || !ft_strncmp(line, word,
			ft_strlen(line) + ft_strlen(word)))
		return (1);
	return (0);
}

static void	mini_handle_null_or_delimiter(char *line, char *word,
		int status, int hd_file_fd)
{
	if (line == NULL)
	{
		if (status != 130)
			ft_printf_fd(STDERR_FILENO, "minishell: warning: here-document\
delimited by end-of-file (wanted `%s\')\n", word);
		free(line);
		close(hd_file_fd);
	}
	else if (!ft_strncmp(line, word, ft_strlen(line) + ft_strlen(word)))
	{
		free(line);
		close(hd_file_fd);
	}
}

static int	mini_create_file(t_mini *mini, t_token *token_node)
{
	int			fd;
	char		*file_index_str;
	char		*file_name;

	file_index_str = ft_itoa(mini->hd_file_index);
	file_name = ft_strjoin("heredoc", file_index_str);
	ft_collect_mem(file_name);
	token_node->token = file_name;
	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 420);
	free(file_index_str);
	mini->hd_file_index++;
	return (fd);
}
