/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   93_builtin_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 15:40:32 by oabdelka          #+#    #+#             */
/*   Updated: 2025/02/03 12:51:47 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"
#include "../include/trashman.h"

// void	mini_exit(t_token *arg, int status_last_cmd)
// {
// 	int	status;

// 	status = status_last_cmd;
// 	if (arg)
// 		status = ft_atoi(arg->token);
// 	ft_free_trashman(ft_get_mem_address());
// 	ft_free_trashman_env(ft_get_mem_address_env());
// 	exit(status);
// }

int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

long	ft_atol(const char *str)
{
	long	num;
	int		sign;

	num = 0;
	sign = 1;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
		sign = 1 - 2 * (*(str++) == '-');
	while (ft_isdigit(*str))
	{
		num = num * 10 + (*str - '0');
		str++;
	}
	return (num * sign);
}

void	exit_clean(t_mini *mini, int status)
{
	(void)mini;
	ft_free_trashman(ft_get_mem_address());
	ft_free_trashman_env(ft_get_mem_address_env());
	exit(status);
}

int	mini_exit(t_token *args, int last_status, t_mini *mini)
{
	long	status;

	ft_printf_fd(1, "exit\n");
	if (!args)
		exit_clean(mini, last_status);
	if (!is_valid_number(args->token))
	{
		ft_printf_fd(2, "minishell: exit: %s: numeric argument required\n",
			args->token);
		exit_clean(mini, 2);
	}
	if (args->next)
	{
		ft_printf_fd(2, "minishell: exit: too many arguments\n");
		mini->status = 1;
		return (1);
	}
	status = ft_atol(args->token);
	exit_clean(mini, (unsigned char)(status % 256));
	return (0);
}
