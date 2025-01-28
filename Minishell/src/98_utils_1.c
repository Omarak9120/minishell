/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   98_utils_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:39:32 by josfelip          #+#    #+#             */
/*   Updated: 2024/06/17 12:35:17 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/libftplus.h"
#include "../include/dictionary.h"

#define NAME 100
#define ERROR 200
#define VALUE 300

int	mini_env_identifier(char *str, t_dict **env_list, int start, int state)
{
	char	*new_entry[2];
	size_t	i;

	new_entry[1] = NULL;
	i = -1;
	while (++i < ft_strlen(str) + 1)
	{
		state = mini_env_get_next_state(state, mini_env_get_column(str[i]));
		if (state == NAME)
		{
			new_entry[0] = ft_substr_mem(str, start, i - start);
			start = i + 1;
			state = 2;
		}
		if (state == VALUE)
			new_entry[1] = ft_substr_mem(str, start, i - start);
		if (state == ERROR)
		{
			ft_putstr_fd("export: not a valid identifier\n", STDERR_FILENO);
			return (1);
		}
	}
	ft_dict_insert(env_list, new_entry);
	return (0);
}

int	mini_env_get_next_state(int state, int column)
{
	static int	truth_table[3][5] = {
	{200, 001, 200, 200, 200},
	{200, 001, 001, 100, 100},
	{002, 002, 002, 002, 300}
	};

	return (truth_table[state][column]);
}

int	mini_env_get_column(char c)
{
	if (ft_isalpha(c) || c == '_')
		return (1);
	if (ft_isdigit(c))
		return (2);
	if (c == '=')
		return (3);
	if (c == '\0')
		return (4);
	return (0);
}
