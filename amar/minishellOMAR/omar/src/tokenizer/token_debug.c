/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 16:00:11 by oabdelka          #+#    #+#             */
/*   Updated: 2024/12/25 16:00:59 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../includes/minishell.h"

// void	printcmds(t_data *data)
// {
// 	t_tokens	*tmp;
// 	const char	*type_names[] = {"DEFID", "WORD", "INFILE", "OUTFILE",
// 		"HEREDOC", "OUTAPPEND", "COMMAND", "OPERATOR", "PIPE", "SPACE",
// 		"FILE"};

// 	tmp = data->cmdchain;
// 	while (tmp != NULL)
// 	{
// 		printf("[%s] %s\n", type_names[tmp->id], tmp->content);
// 		tmp = tmp->next;
// 	}
// }
