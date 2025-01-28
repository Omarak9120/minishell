/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_utils_5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:28:04 by gfantoni          #+#    #+#             */
/*   Updated: 2024/06/20 10:43:28 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	mini_last_char_is_equal(char *token);
static char	*mini_join_export_arg(char *token, char *token_next);

int	mini_was_quoted(int state)
{
	if (state == 107 || state == 108)
		return (1);
	return (0);
}

int	mini_was_squoted(int state)
{
	if (state == 108)
		return (1);
	return (0);
}

void	mini_handle_export_arg(t_mini *mini)
{
	t_token	*token_node;

	token_node = mini->token_list;
	while (token_node)
	{
		if (token_node->gender == WORD
			&& mini_last_char_is_equal(token_node->token)
			&& token_node->next && token_node->next->was_quoted)
		{
			token_node->token = mini_join_export_arg(token_node->token,
					token_node->next->token);
			token_node->next = NULL;
		}
		token_node = token_node->next;
	}
}

static int	mini_last_char_is_equal(char *token)
{
	size_t	len;

	if (token && token[0] != '\0')
	{
		len = ft_strlen(token);
		if (token[len - 1] == '=')
			return (1);
	}
	return (0);
}

static char	*mini_join_export_arg(char *token, char *token_next)
{
	char	*joined_token;

	joined_token = ft_strjoin(token, token_next);
	ft_collect_mem(joined_token);
	return (joined_token);
}
