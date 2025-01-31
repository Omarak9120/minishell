/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   13_remake_environ.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 18:42:16 by gfantoni          #+#    #+#             */
/*   Updated: 2025/01/31 16:57:25 by oabdelka         ###   ########.fr       */
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
mini->mini_environ = [ "PATH=/usr/bin:/bin", "HOME=/home/user", "TERM=xterm-256color", NULL ].
*/