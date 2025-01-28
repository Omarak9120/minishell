/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   93_builtin_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:34:02 by josfelip          #+#    #+#             */
/*   Updated: 2024/06/17 12:18:24 by josfelip         ###   ########.fr       */
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
