/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_utils_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:08:03 by oabdelka          #+#    #+#             */
/*   Updated: 2025/02/01 19:08:05 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_end_state(int num)
{
	if (num >= 100)
		return (1);
	return (0);
}

void	syntonize_index(t_dfa *dfa)
{
	if (mini_is_back_state(dfa->state))
		dfa->i--;
	if (mini_is_quote_state(dfa->state))
	{
		dfa->start++;
		dfa->quote = 1;
	}
}

int	mini_is_back_state(int num)
{
	if (num == 100 || num == 101 || num == 103 || num == 105)
		return (1);
	return (0);
}

int	mini_is_quote_state(int num)
{
	if (num == 107 || num == 108)
		return (1);
	return (0);
}

int	is_error_state(int num)
{
	if (num >= 200)
		return (1);
	return (0);
}
