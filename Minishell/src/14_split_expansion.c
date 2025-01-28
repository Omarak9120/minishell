/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   14_split_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:56:57 by gfantoni          #+#    #+#             */
/*   Updated: 2024/06/17 18:36:19 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	mini_find_space(t_mini *mini, int i);
void	mini_split_and_link(t_token *token_node);

void	mini_split_expansion_in_nodes(t_mini *mini)
{
	int		i;
	t_token	*cmd;

	i = 0;
	cmd = mini->commands[i];
	while (cmd)
	{
		mini_find_space(mini, i);
		i++;
		cmd = mini->commands[i];
	}
}

void	mini_find_space(t_mini *mini, int i)
{
	t_token	*token_node;

	token_node = mini->commands[i];
	while (token_node && token_node->token)
	{
		if (ft_strchr(token_node->token, ' '))
		{
			mini_split_and_link(token_node);
			mini_find_space(mini, i);
		}
		token_node = token_node->next;
	}
}

void	mini_split_and_link(t_token *token_node)
{
	int		i;
	t_token	*saved_next;
	t_token	*token_node_new_curr;
	t_token	*token_node_curr;
	char	**splited_token;

	token_node_curr = token_node;
	saved_next = token_node->next;
	splited_token = ft_split(token_node->token, ' ');
	ft_collect_mem(splited_token);
	ft_collect_mem(splited_token[0]);
	token_node_curr->token = splited_token[0];
	i = 1;
	while (splited_token[i])
	{
		ft_collect_mem(splited_token[i]);
		token_node_new_curr = mini_token_lstnew(splited_token[i], 100);
		token_node_curr->next = token_node_new_curr;
		token_node_curr = token_node_curr->next;
		i++;
	}
	token_node_new_curr->next = saved_next;
}
