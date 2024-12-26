/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjamil <mjamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 14:32:03 by mjamil            #+#    #+#             */
/*   Updated: 2024/12/25 14:32:03 by mjamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//validate_numeric_argument
int	check_status_str(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

//modulate_exit_status
int	calculate_exit_status(int status)
{
	if (status < 0)
		return (256 + (status % 256));
	return (status % 256);
}

//check_and_convert_exit_code
int	convert_and_validate_exit_status(char *arg)
{
	int	exit_status;

	if (!check_status_str(arg))
	{
		printf("exit : %s numeric argument needed\n", arg);
		return (1);
	}
	exit_status = ft_atoi(arg);
	return (calculate_exit_status(exit_status));
}

//too_many_args_error
int	handle_too_many_args_error(void)
{
	printf("exit: too many arguments\n");
	return (1);
}

//exit_shell
int	exit_command(t_arg *args)
{
	int		exit_status;
	t_arg	*arg;

	arg = args->next;
	if (arg && arg->next)
	{
		exit_status = 1;
		return (handle_too_many_args_error());
	}
	if (arg)
		exit_status = convert_and_validate_exit_status(arg->arg);
	else
		exit_status = 0;
	free_list_arg(arg);
	return (exit(exit_status), exit_status);
}
