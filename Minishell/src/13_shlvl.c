/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   13_shlvl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 20:06:45 by oabdelka          #+#    #+#             */
/*   Updated: 2025/02/03 20:07:14 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	mini_update_shlvl(t_mini *mini)
{
	static int	updated = 0;
	t_dict		*shlvl_node;

	if (updated)
		return ;
	shlvl_node = mini_get_env_node(mini, "SHLVL");
	if (!shlvl_node)
		mini_create_shlvl(mini);
	else
		mini_increment_shlvl(shlvl_node);
	updated = 1;
}

void	mini_create_shlvl(t_mini *mini)
{
	char	*shlvl_var[2];

	shlvl_var[0] = ft_strdup("SHLVL");
	shlvl_var[1] = ft_strdup("1");
	ft_dictadd_back(&mini->env_list, ft_dictnew(shlvl_var));
	ft_collect_mem(shlvl_var[0]);
	ft_collect_mem(shlvl_var[1]);
}

void	mini_increment_shlvl(t_dict *shlvl_node)
{
	int		level;
	char	*new_shlvl;

	level = ft_atoi(shlvl_node->value);
	if (level < 0)
		level = 0;
	new_shlvl = ft_itoa(level + 1);
	ft_collect_mem(new_shlvl);
	if (!ft_is_tracked(shlvl_node->value))
		free(shlvl_node->value);
	shlvl_node->value = new_shlvl;
}
