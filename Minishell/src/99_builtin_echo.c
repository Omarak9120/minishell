/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   99_builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:10:42 by oabdelka          #+#    #+#             */
/*   Updated: 2025/02/01 19:10:44 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/dictionary.h"

int	mini_echo(t_token *arg)
{
	int	new_line;

	new_line = 1;
	if (arg && arg->token && arg->token[0] == '-')
	{
		new_line = mini_add_new_line(arg->token);
		if (new_line == 0)
			arg = arg->next;
	}
	while (arg)
	{
		ft_printf("%s", arg->token);
		arg = arg->next;
		if (arg)
			ft_printf(" ");
	}
	if (new_line)
		ft_printf("\n");
	return (0);
}

int	mini_add_new_line(char *str)
{
	int	i;

	i = 1;
	if (str[i] == '\0')
		return (1);
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}
