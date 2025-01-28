/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   97_utils_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:22:08 by josfelip          #+#    #+#             */
/*   Updated: 2024/06/19 11:17:06 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/dictionary.h"

#define ERROR 200

int	mini_valid_identifier(char *str, int state)
{
	size_t	i;

	i = -1;
	while (++i < ft_strlen(str) + 1)
	{
		state = mini_env_get_next_state(state, mini_env_get_column(str[i]));
		if (state == ERROR)
		{
			ft_putstr_fd("bash: line 0: unset: `", STDERR_FILENO);
			ft_putstr_fd(str, STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			return (1);
		}
	}
	return (0);
}
