/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   15_utils_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:23:01 by gfantoni          #+#    #+#             */
/*   Updated: 2024/06/17 18:29:42 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	mini_init_hd(t_mini *hd, char *line);
static void	mini_hd_tokenizer(t_mini *hd);
static void	mini_hd_parser(t_mini *hd);
static char	*mini_join_exp_list(t_token *token_node);

char	*mini_hd_expansion(char *line)
{
	t_mini	hd;
	char	*exp_line;

	if (!ft_strchr(line, '$'))
		return (line);
	mini_init_hd(&hd, line);
	mini_getenv(&hd);
	mini_hd_tokenizer(&hd);
	mini_hd_parser(&hd);
	mini_expansion(&hd);
	exp_line = mini_join_exp_list(hd.commands[0]);
	return (exp_line);
}

static char	*mini_join_exp_list(t_token *token_node)
{
	char	*str;
	char	*tmp;

	str = NULL;
	while (token_node)
	{
		if (!str)
			tmp = ft_strdup("");
		else
			tmp = ft_strjoin(str, " ");
		str = ft_strjoin(tmp, token_node->token);
		free(tmp);
		ft_collect_mem(str);
		token_node = token_node->next;
	}
	return (str);
}

static void	mini_init_hd(t_mini *hd, char *line)
{
	hd->path = NULL;
	hd->lst_memory = NULL;
	hd->status = 0;
	hd->cmd_line = line;
	hd->pathname = NULL;
	hd->token_list = NULL;
	hd->env_list = NULL;
	hd->cmd_exec_list = NULL;
	hd->syntax_error = 0;
	hd->mini_environ = NULL;
	hd->hd_file_index = 0;
}

static void	mini_hd_tokenizer(t_mini *hd)
{
	t_dfa	dfa;

	mini_init_dfa(&dfa);
	mini_automaton(hd, &dfa);
}

static void	mini_hd_parser(t_mini *hd)
{
	hd->commands = (t_token **)ft_calloc(sizeof(t_token *), 2);
	ft_collect_mem(hd->commands);
	hd->commands[0] = hd->token_list;
}
