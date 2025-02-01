/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   98_builtin_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:10:34 by oabdelka          #+#    #+#             */
/*   Updated: 2025/02/01 19:10:35 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/dictionary.h"

int	mini_export(t_token *arg, t_dict **env_list)
{
	int		exit_status;
	int		tmp;
	t_token	*cur;

	exit_status = 0;
	cur = arg;
	if (!cur)
		ft_dict_print(ft_dictsort(*env_list));
	while (cur)
	{
		tmp = mini_env_identifier(cur->token, env_list, 0, 0);
		if (tmp)
			exit_status = tmp;
		cur = cur->next;
	}
	return (exit_status);
}
