/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   13_remake_environ.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:09:53 by oabdelka          #+#    #+#             */
/*   Updated: 2025/02/03 15:52:45 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 *   Rebuilds the mini->mini_environ array from the linked list mini->env_list,
 *   forming typical strings "KEY=VALUE" for each environment variable. This 
 *   freshly allocated char** can be passed to execve so child processes see 
 *   all current environment changes (like exports, unsets, etc.).
 */

static int	mini_get_env_list_size(t_dict *env_list);

void	mini_remake_environ(t_mini *mini)
{
	t_dict	*env_list;
	char	**mini_environ;
	char	*key_plus_equal;
	char	*mini_environ_curr;
	int		i;

	env_list = mini->env_list;
	// update_shlvl(mini);
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
// void update_shlvl(t_mini *mini)
// {
// 	char	*shlvl_str;
// 	int	shlvl;
// 	char	*new_shlvl;
// 	char	*new_var[2];
//
// 	shlvl_str = ft_dict_get_value(mini->env_list, "SHLVL");
//     if (shlvl_str)
//         shlvl = ft_atoi(shlvl_str) + 1;
//     else
//         shlvl = 1;
//     if (shlvl >= 1000)
//         shlvl = 1; 
//     new_shlvl = ft_itoa(shlvl);
//     new_var[0] = "SHLVL";
//     new_var[1] = new_shlvl;
//     ft_dict_update(mini->env_list, new_var);
//     free(new_shlvl);
// }
/*
mini->mini_environ = [
    "PATH=/usr/bin:/bin", 
    "HOME=/Users/username", 
    "SHELL=/bin/zsh", 
    ...
    NULL
]

[Node #1] key="PATH", value="/usr/bin:/bin"
    next
[Node #2] key="HOME", value="/home/user"
    next
[Node #3] key="TERM", value="xterm-256color"
    next
NULL


We build strings:
"PATH=/usr/bin:/bin"
"HOME=/home/user"
"TERM=xterm-256color"

Then we build an array of strings:
mini->mini_environ = [ "PATH=/usr/bin:/bin",
						 "HOME=/home/user", 
						 "TERM=xterm-256color",
						  NULL ].
*/