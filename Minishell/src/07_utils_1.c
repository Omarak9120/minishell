/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_utils_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 09:16:02 by josfelip          #+#    #+#             */
/*   Updated: 2025/01/28 15:14:56 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*(__environ)there is a global pointer to an array of char * strings,
each being an environment variable in the form KEY=VALUE*/
void	mini_getenv(t_mini *mini)
{
	int		i;
	int		start;
	int		len;
	char	*var[2];

	mini->env_list = NULL;
	i = 0;
	while (__environ[i])
	{
		start = 0;
		len = mini_strchr_index(__environ[i], '=');
		if (len > -1)
		{
			var[0] = ft_substr(__environ[i], start, len);
			ft_collect_mem_env(var[0]);
			start = len + 1;
			len = ft_strlen(__environ[i]) - start;
			var[1] = ft_substr(__environ[i], start, len);
			ft_collect_mem_env(var[1]);
			ft_dictadd_back(&mini->env_list, ft_dictnew_env(var));
		}
		i++;
	}
}

int	mini_strchr_index(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}
/*[ "Hi", "$USER" -> "omar", "123" ] "Hiomar123" */
char	*mini_sub_token_join(t_sub_token *sub_token_lst)
{
	char	*sub_token;
	char	*str;

	str = NULL;
	while (sub_token_lst)
	{
		sub_token = sub_token_lst->content;
		if (sub_token)
		{
			if (str)
				str = ft_strjoin(str, sub_token);
			else
				str = ft_strdup(sub_token);
			ft_collect_mem(str);
		}
		sub_token_lst = sub_token_lst->next;
	}
	return (str);
}

char	*mini_get_dollar_sign(t_mini *mini, char *sub_token)
{
	char	*status;
	char	*status_joined;

	status = ft_itoa(mini->status);
	ft_collect_mem(status);
	if (sub_token[2] != '\0')
	{
		sub_token++;
		sub_token++;
		status_joined = ft_strjoin(status, sub_token);
		ft_collect_mem(status_joined);
		return (status_joined);
	}
	return (status);
}
