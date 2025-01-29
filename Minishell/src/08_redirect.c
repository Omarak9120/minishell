/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:24:02 by oabdelka          #+#    #+#             */
/*   Updated: 2025/01/29 14:24:05 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	mini_redirect(t_mini *mini)
{
	int		i;
	t_token	*token_node;

	i = 0;
	token_node = mini->commands[i];
	while (token_node)
	{
		mini_find_redirect(mini, i);
		i++;
		token_node = mini->commands[i];
	}
}

void	mini_find_redirect(t_mini *mini, int i)
{
	t_cmd	*redir_node;
	t_token	*token_node;

	redir_node = mini_redir_lstnew();
	token_node = mini->commands[i];
	while (token_node)
	{
		if (token_node->specie == OUT_REDIRECT)
			mini_handle_out_redir(redir_node, token_node->next->token);
		else if (token_node->specie == IN_REDIRECT)
			mini_handle_in_redir(redir_node, token_node->next->token);
		else if (token_node->specie == APPEND)
			mini_handle_append_redir(redir_node, token_node->next->token);
		else if (token_node->specie == HERE_DOC)
			mini_handle_heredoc_redir(redir_node, token_node->next->token);
		token_node = token_node->next;
	}
	mini_redir_lstadd_back(&mini->cmd_exec_list, redir_node);
}
