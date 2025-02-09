/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   94_builtin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:10:14 by oabdelka          #+#    #+#             */
/*   Updated: 2025/02/03 14:33:33 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

static void	mini_printenv(t_dict *dict);

int	env(t_token *arg, t_dict **dict)
{
	if (!arg)
		mini_printenv(*dict);
	return (0);
}

static void	mini_printenv(t_dict *dict)
{
	t_dict	*cur;

	cur = ft_dictsort(dict);
	while (cur)
	{
		if (cur->value)
			ft_printf("%s=%s\n", cur->key, cur->value);
		cur = cur->next;
	}
}
/*
int	env(t_token *arg, t_dict **dict)
{
	if (arg)
	{
		ft_printf_fd(2, "minishell: env: too many arguments\n");
		return (1);
	}
	mini_printenv(*dict);
	return (0);
}*/
