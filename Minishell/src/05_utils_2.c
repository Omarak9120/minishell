/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:08:07 by oabdelka          #+#    #+#             */
/*   Updated: 2025/02/01 19:08:09 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	mini_print_sintax_error_message(int state)
{
	if (state == 200)
		ft_printf_fd(STDERR_FILENO, "minishell: syntax error: \
unterminated quoted string\n");
	else if (state == 201)
		ft_printf_fd(STDERR_FILENO, "minishell: syntax error \
near unexpected token\n");
	else if (state == 202)
		ft_printf_fd(STDERR_FILENO, "minishell: syntax error: \
not a bonus project '||'\n");
}
/*
mini->cmd_line is your full input.
dfa->start is the index where this token began.
dfa->i is the index where you reached the end state.
+ 1: The substring length includes the character at position dfa->i.
- dfa->quote: If you ended inside a quoted segment.
*/
void	mini_cut_string(t_mini *mini, t_dfa *dfa)
{
	dfa->value = ft_substr(mini->cmd_line, dfa->start,
			(dfa->i - dfa->start) + 1 - dfa->quote);
	ft_collect_mem(dfa->value);
	mini_token_lstadd_back(&mini->token_list,
		mini_token_lstnew(dfa->value, dfa->state));
	dfa->state = 0;
	dfa->quote = 0;
}

void	mini_set_syntax_error(t_mini *mini)
{
	ft_printf_fd(STDERR_FILENO, "minishell: syntax error \
near unexpected token\n");
	mini->syntax_error = 1;
	mini->status = 2;
}
