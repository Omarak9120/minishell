/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   93_builtin_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:34:02 by josfelip          #+#    #+#             */
/*   Updated: 2025/01/31 17:55:29 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"
#include "../include/trashman.h"

void	mini_exit(t_token *arg, int status_last_cmd)
{
	int	status;

	status = status_last_cmd;
	if (arg)
		status = ft_atoi(arg->token);
	ft_free_trashman(ft_get_mem_address());
	ft_free_trashman_env(ft_get_mem_address_env());
	exit(status);
}

// // Checks if 'str' is a valid integer (optional +/- sign). Returns 1 if numeric, else 0.
// int	mini_is_numeric(const char *str)
// {
// 	int i;

// 	if (!str || !str[0])
// 		return 0;
// 	i = 0;
// 	if (str[i] == '+' || str[i] == '-')
// 		i++;
// 	if (!str[i])
// 		return 0;
// 	while (str[i])
// 	{
// 		if (str[i] < '0' || str[i] > '9')
// 			return 0;
// 		i++;
// 	}
// 	return 1;
// }

// // Counts how many arguments are in the linked list 'arg'.
// int	mini_count_args(t_token *arg)
// {
// 	int count = 0;
// 	while (arg)
// 	{
// 		count++;
// 		arg = arg->next;
// 	}
// 	return count;
// }

// // Frees all shell resources and exits with 'code'.
// void	mini_free_all_and_exit(int code)
// {
// 	ft_free_trashman(ft_get_mem_address());
// 	ft_free_trashman_env(ft_get_mem_address_env());
// 	exit(code);
// }

// // Gets exit code from a single string argument. If non-numeric, returns -1.
// int	mini_get_exit_code(char *arg)
// {
// 	if (!mini_is_numeric(arg))
// 		return -1;
// 	return ft_atoi(arg);
// }

// // The main exit function, handles all Bash-like cases.
// void	mini_exit(t_token *arg, int last_status)
// {
// 	int argc;
// 	int code;

// 	ft_printf_fd(STDERR_FILENO, "exit\n");
// 	argc = mini_count_args(arg);
// 	if (argc > 1)
// 	{
// 		ft_printf_fd(STDERR_FILENO, "bash: exit: too many arguments\n");
// 		return;
// 	}
// 	if (argc == 0)
// 		mini_free_all_and_exit(last_status);
// 	code = mini_get_exit_code(arg->token);
// 	if (code < 0)
// 	{
// 		ft_printf_fd(STDERR_FILENO, 
// 			"bash: exit: %s: numeric argument required\n", arg->token);
// 		mini_free_all_and_exit(255);
// 	}
// 	mini_free_all_and_exit(code);
// }
