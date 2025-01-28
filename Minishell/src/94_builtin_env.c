/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   94_builtin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:34:02 by josfelip          #+#    #+#             */
/*   Updated: 2024/06/19 17:11:05 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

static void	mini_printenv(t_dict *dict);

int	mini_env(t_token *arg, t_dict **dict)
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
