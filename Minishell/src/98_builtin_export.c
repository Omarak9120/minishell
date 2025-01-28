/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   98_builtin_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:56:46 by josfelip          #+#    #+#             */
/*   Updated: 2024/06/18 15:21:54 by gfantoni         ###   ########.fr       */
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
