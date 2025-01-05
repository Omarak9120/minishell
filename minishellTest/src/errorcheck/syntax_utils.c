/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 02:01:47 by odib              #+#    #+#             */
/*   Updated: 2025/01/05 12:53:40 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_tokens	*getprev(t_tokens *token)
{
	t_tokens	*tmp;

	tmp = token;
	while (tmp && tmp->id == TOKEN_SPACE)
		tmp = tmp->previous;
	return (tmp);
}

t_tokens	*getnext(t_tokens *token)
{
	if (token && token->next && token->next->id == TOKEN_SPACE)
		token = token->next;
	if (token && token->next)
		return (token->next);
	return (NULL);
}

// int	checkpipe(t_tokens *token)
// {
// 	if (!getnext(token->next) || (getnext(token->next)->id != TOKEN_WORD
// 			&& getnext(token->next)->id != TOKEN_COMMAND)
// 		|| !getprev(token->previous)
// 		|| (getprev(token->previous)->id != TOKEN_WORD
// 			&& getprev(token->previous)->id != TOKEN_COMMAND))
// 	{
// 		if (getprev(token->previous))
// 			getprev(token->previous)->error = 1;
// 		if (getnext(token->next))
// 			getnext(token->next)->error = 1;
// 		return (1);
// 	}
// 	return (0);
// }

int checkpipe(t_tokens *token)
{
    t_tokens *next_non_space;
    t_tokens *prev_non_space;

	next_non_space = getnext(token->next);
	prev_non_space = getprev(token->previous);
    if (!next_non_space 
        || (next_non_space->id != TOKEN_WORD && next_non_space->id != TOKEN_COMMAND)
        || !prev_non_space 
        || (prev_non_space->id != TOKEN_WORD && prev_non_space->id != TOKEN_COMMAND))
    {
        if (prev_non_space)
            prev_non_space->error = 1;
        if (next_non_space)
            next_non_space->error = 1;
        return (1);
    }
    return (0);
}

int	checkfileoutappend(t_tokens *token)
{
	if (!getnext(token->next) || getnext(token->next)->id != TOKEN_WORD)
		return (1);
	return (0);
}

int	checkheredoc(t_tokens *token)
{
	t_tokens	*next_token;

	next_token = getnext(token->next);
	if (!next_token || (next_token->id != TOKEN_FILE))
		return (1);
	return (0);
}
