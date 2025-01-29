/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:24:02 by oabdelka          #+#    #+#             */
/*   Updated: 2025/01/29 18:35:11 by oabdelka         ###   ########.fr       */
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
/*
#include "../include/minishell.h"

void    mini_redirect(t_mini *mini)
{
    int     i;
    t_token *token_node;

    i = 0;
    while ((token_node = mini->commands[i]))
    {
        mini_find_redirect(mini, i);
        if (mini->status != 0)
            break;
        i++;
    }
}

static void process_redirects(t_mini *mini, t_token *token_node, t_cmd *redir_node)
{
    while (token_node)
    {
        if (token_node->specie == OUT_REDIRECT)
            mini_handle_out_redir(mini, redir_node, token_node->next->token);
        else if (token_node->specie == IN_REDIRECT)
            mini_handle_in_redir(mini, redir_node, token_node->next->token);
        else if (token_node->specie == APPEND)
            mini_handle_append_redir(mini, redir_node, token_node->next->token);
        else if (token_node->specie == HERE_DOC)
            mini_handle_heredoc_redir(mini, redir_node, token_node->next->token);
        
        if (mini->status != 0)
            break;
        token_node = token_node->next;
    }
}

void    mini_find_redirect(t_mini *mini, int i)
{
    t_cmd   *redir_node;
    t_token *token_node;

    redir_node = mini_redir_lstnew();
    token_node = mini->commands[i];
    
    // Process input redirections first
    process_redirects(mini, token_node, redir_node);
    
    // Only add to list if no errors
    if (mini->status == 0)
        mini_redir_lstadd_back(&mini->cmd_exec_list, redir_node);
    else
        mini_redir_lstdelone(redir_node);
}*/