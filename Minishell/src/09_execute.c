/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   09_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:11:27 by gfantoni          #+#    #+#             */
/*   Updated: 2024/06/18 15:21:32 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	mini_execute(t_mini *mini)
{
	mini_build_cmd_exec(mini);
	mini_get_cmd_exec_path(mini);
	mini_open_pipes(mini);
	mini_remake_environ(mini);
	mini_execve(mini);
}

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
