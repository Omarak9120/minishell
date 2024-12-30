/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expansion2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjamil <mjamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 19:52:30 by mjamil            #+#    #+#             */
/*   Updated: 2024/12/30 19:52:30 by mjamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//extract_before_dollar
static char *get_before_part(const char *input_str, int *position)
{
	int quote_status = 0;
	int index = 0;

	while (input_str[index] != '$' && input_str[index] != '\0')
	{
		if (input_str[index] == '"')
			quote_status = !quote_status;
		if (input_str[index] == '\'' && !quote_status)
		{
			index++;
			while (input_str[index] != '\'' && input_str[index] != '\0')
				index++;
		}
		index++;
	}
	*position = index;
	return (ft_strndup(input_str, index));
}

//extract_key_and_remaining
static char *get_key_and_after(const char *input_str, int start_position)
{
	int quote_status = 0;
	int index = start_position;

	while (input_str[index] != ' ' && input_str[index] != '\0' 
		   && input_str[index] != '\"' && input_str[index] != '\'')
	{
		if (input_str[index] == '"')
			quote_status = !quote_status;
		if (input_str[index] == '\'' && !quote_status)
		{
			index++;
			while (input_str[index] != '\'' && input_str[index] != '\0')
				index++;
		}
		else
			index++;
	}
	return (ft_strdup(input_str + start_position));
}

//substitute_key_with_value
static char	*replace_key_with_value(const char *before,
	char *key_and_after, t_data *data)
{
	char *final_result;
	char *env_value;
	char *key;
	char *remaining_str;

	key = ft_strndup(key_and_remaining, ft_strchr(key_and_remaining, ' ') - key_and_remaining);
	remaining_str = ft_strdup(ft_strchr(key_and_remaining, ' '));
	free(key_and_remaining);

	env_value = envvaluestr(key + 1, env_data);

	final_result = ft_strjoingnl(ft_strdup(""), before_part);
	final_result = ft_strjoingnl(final_result, env_value);
	final_result = ft_strjoingnl(final_result, remaining_str);

	free(env_value);
	free(key);
	free(remaining_str);

	return (final_result);
}

//expand_env_variable
char *concatenvloop(char *input_str, t_data *env_data)
{
	int before_position;
	char *before_part;
	char *key_and_remaining;
	char *updated_input;

	before_part = extract_before_dollar(input_str, &before_position);
	key_and_remaining = extract_key_and_remaining(input_str, before_position);
	free(input_str);

	updated_input = substitute_key_with_value(before_part, key_and_remaining, env_data);
	free(before_part);

	return (updated_input);
}
