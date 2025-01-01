/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_skipper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjamil <mjamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:09:50 by mjamil            #+#    #+#             */
/*   Updated: 2024/12/30 16:09:50 by mjamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//advance_past_non_alpha_var
static int	skip_non_alpha_var(char *input, int index)
{
	if (input[index] == '$' && !ft_isalpha(input[index + 1]))
	{
		index++;
		while (input[index] != ' ' && input[index] != '\0'
			&& input[index] != '\"')
			index++;
	}
	return (index);
}

//switch_quote_mode
static int	toggle_in_quote(char character, int in_quote)
{
	if (character == '"')
		return (!in_quote);
	return (in_quote);
}

//advance_past_single_quotes
static int	skip_single_quote_section(char *input, int index)
{
	if (input[index] == '\'')
	{
		index++;
		while (input[index] != '\'' && input[index] != '\0')
			index++;
		if (input[index] == '\'')
			index++;
	}
	return (index);
}

//is_quote_char
int	is_quote(char character)
{
	return (character == '\'' || character == '\"');
}

//calculate_dollar_signs
int	count_dollar_signs(char *input)
{
	int		index;
	int		dollar_sign_count;
	int		inside_quotes;

	index = 0;
	dollar_sign_count = 0;
	inside_quotes = 0;
	while (input[index] != '\0')
	{
		index = skip_non_alpha_var(input, index);
		if (input[index] == '$')
			dollar_sign_count++;
		inside_quotes = toggle_in_quote(input[index], inside_quotes);
		index = skip_single_quote_section(input, index);
		index++;
	}
	return (dollar_sign_count);
}
