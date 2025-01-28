/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_utils_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 10:18:47 by gfantoni          #+#    #+#             */
/*   Updated: 2024/06/17 18:44:09 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	mini_is_end_state(int num)
{
	if (num >= 100)
		return (1);
	return (0);
}

void	mini_syntonize_index(t_dfa *dfa)
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

int	mini_is_error_state(int num)
{
	if (num >= 200)
		return (1);
	return (0);
}
