/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   97_builtin_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:10:26 by oabdelka          #+#    #+#             */
/*   Updated: 2025/02/01 19:10:27 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/dictionary.h"

int	mini_unset(t_token *arg, t_dict **dict)
{
	if (!arg)
		return (0);
	if (mini_valid_identifier(arg->token, 0))
		return (1);
	ft_dictdel_entry(dict, arg->token);
	return (0);
}
