/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   13_remake_environ.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 18:42:16 by gfantoni          #+#    #+#             */
/*   Updated: 2024/06/19 11:25:01 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	mini_get_env_list_size(t_dict *env_list);

void	mini_remake_environ(t_mini *mini)
{
	t_dict	*env_list;
	char	**mini_environ;
	char	*key_plus_equal;
	char	*mini_environ_curr;
	int		i;

	env_list = mini->env_list;
	mini_environ = (char **)ft_calloc(sizeof(char *),
			mini_get_env_list_size(env_list) + 1);
	ft_collect_mem(mini_environ);
	i = 0;
	while (env_list)
	{
		key_plus_equal = ft_strjoin(env_list->key, "=");
		ft_collect_mem(key_plus_equal);
		mini_environ_curr = ft_strjoin(key_plus_equal, env_list->value);
		ft_collect_mem(mini_environ_curr);
		mini_environ[i] = mini_environ_curr;
		env_list = env_list->next;
		i++;
	}
	mini->mini_environ = mini_environ;
}

static int	mini_get_env_list_size(t_dict *env_list)
{
	int	i;

	i = 0;
	while (env_list)
	{
		i++;
		env_list = env_list->next;
	}
	return (i);
}
