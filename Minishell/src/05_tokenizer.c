/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:07:59 by oabdelka          #+#    #+#             */
/*   Updated: 2025/02/02 17:03:04 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	tokenizer(t_mini *mini)
{
	t_dfa	dfa;

	init_dfa(&dfa);
	if (mini->cmd_line)
	{
		if (mini->cmd_line[0] == '\0')
			return ;
		mini_automaton(mini, &dfa);
		if (!mini->syntax_error)
			mini_check_sintax(mini, mini->token_list);
		mini_handle_export_arg(mini);
	}
}

void	init_dfa(t_dfa *dfa)
{
	dfa->value = NULL;
	dfa->size = 0;
	dfa->start = 0;
	dfa->state = 0;
	dfa->quote = 0;
	dfa->i = 0;
}

void	mini_automaton(t_mini *mini, t_dfa *dfa)
{
	dfa->size = ft_strlen(mini->cmd_line) + 1;
	while (dfa->i < dfa->size)
	{
		if (dfa->state == 0)
			dfa->start = dfa->i;
		dfa->state = mini_get_next_state(dfa->state, \
		mini_get_column(mini->cmd_line[dfa->i]));
		if (mini_is_end_state(dfa->state) && dfa->state != NULL_CHAR)
		{
			mini_syntonize_index(dfa);
			if (mini_is_error_state(dfa->state))
			{
				mini_print_sintax_error_message(dfa->state);
				mini->status = 2;
				mini->syntax_error = 1;
				break ;
			}
			mini_cut_string(mini, dfa);
		}
		dfa->i++;
	}
}

int	mini_get_next_state(int state, int column)
{
	static int	truth_table[7][8] = {
	{001, 002, 003, 004, 005, 006, 000, 666},
	{001, 100, 100, 100, 100, 100, 100, 100},
	{101, 102, 101, 101, 101, 101, 101, 101},
	{103, 103, 104, 103, 103, 103, 103, 103},
	{004, 004, 004, 107, 004, 004, 004, 200},
	{005, 005, 005, 005, 108, 005, 005, 200},
	{105, 105, 105, 105, 105, 001, 105, 201}
	};

	return (truth_table[state][column]);
}

int	mini_get_column(char c)
{
	if (c == '>')
		return (1);
	if (c == '<')
		return (2);
	if (c == '\"')
		return (3);
	if (c == '\'')
		return (4);
	if (c == '|')
		return (5);
	if ((c >= '\t' && c <= '\r') || c == ' ')
		return (6);
	if (c == '\0')
		return (7);
	return (0);
}
