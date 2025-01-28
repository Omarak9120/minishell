/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_utils_6.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 11:16:54 by gfantoni          #+#    #+#             */
/*   Updated: 2024/06/18 11:21:32 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	mini_has_syntax_error(t_mini *mini, t_token *token_list);
static int	mini_pipe_syntax(t_token *token_node);
static int	mini_consecutive_op_syntax(t_token *token_node);
static int	mini_pipe_space_pipe_syntax(t_token *token_node);

void	mini_check_sintax(t_mini *mini, t_token *token_list)
{
	int		stdin_backup;
	int		stdout_backup;

	if (token_list && token_list->token[0] == '|')
	{
		mini_set_syntax_error(mini);
		return ;
	}
	mini_init_hd_signal(mini, &stdin_backup, &stdout_backup);
	while (token_list)
	{
		if (token_list->specie == HERE_DOC
			&& mini_is_valid_heredoc(token_list->next))
			mini_handle_heredoc(mini, token_list->next);
		if (token_list->specie == HERE_DOC
			&& !mini_is_valid_heredoc(token_list->next))
		{
			mini_set_syntax_error(mini);
			return ;
		}
		if (mini_has_syntax_error(mini, token_list))
			return ;
		token_list = token_list->next;
	}
	mini_finish_hd_signal(&stdin_backup, &stdout_backup);
}

static int	mini_has_syntax_error(t_mini *mini, t_token *token_list)
{
	if (mini_pipe_syntax(token_list)
		|| mini_consecutive_op_syntax(token_list)
		|| mini_pipe_space_pipe_syntax(token_list))
	{
		mini_set_syntax_error(mini);
		return (1);
	}
	return (0);
}

static int	mini_pipe_syntax(t_token *token_node)
{
	if (token_node->token[0] == '|' && token_node->next == NULL)
		return (1);
	return (0);
}

static int	mini_consecutive_op_syntax(t_token *token_node)
{
	if (token_node->gender == OPERATOR && token_node->specie != PIPE)
		if (token_node->next && token_node->next->gender == OPERATOR)
			return (1);
	return (0);
}

static int	mini_pipe_space_pipe_syntax(t_token *token_node)
{
	if (token_node->next)
		if (token_node->token[0] == '|' && token_node->next->token[0] == '|')
			return (1);
	return (0);
}
