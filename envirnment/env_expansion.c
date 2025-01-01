/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjamil <mjamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 19:18:55 by mjamil            #+#    #+#             */
/*   Updated: 2024/12/30 19:18:55 by mjamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//get_char_position
int	find_char_index(char *str, char target_char)
{
	int	index;

	index = 0;
	while (str[index] != target_char && str[index] != '\0')
		index++;
	return (index);
}

//get_env_value
char	*envvaluestr(char *key, t_data *shell_data)
{
	t_env	*env_entry;
	char	*value;
	char	*result_value;

	printf("Searching for KEY: %s\n", key);
	if (ft_strlen(key) == 0)
		return (ft_strdup(""));
	env_entry = shell_data->env_list;
	while (env_entry != NULL && ft_strcmp(env_entry->key, key) != 0)
	{
		printf("Checking ENV entry: %s\n", env_entry->key);
		env_entry = env_entry->next;
	}
	if (env_entry == NULL || (ft_strlen(key) != ft_strlen(env_entry->key)))
		return (ft_strdup(""));
	value = env_entry->value;
	result_value = ft_strdup("");
	if (value != NULL)
		result_value = ft_strjoingnl(result_value, value);
	free(key);
	return (result_value);
}

//expand_env_variables
char	*concatenv(char *input_str, t_data *shell_data)
{
	char	*expanded_str;
	char	*temp_expanded_str;

	expanded_str = ft_strdup(input_str);
	while (dollarcount(expanded_str) != 0)
	{
		temp_expanded_str = expanded_str;
		expanded_str = expand_variables_loop(expanded_str, shell_data);
		free(temp_expanded_str);
		printf("Expanded string: %s\n", expanded_str);
	}
	return (expanded_str);
}

//can_expand_variables
int	isexpandable(char *input_str)
{
	t_isexpandable	exp;

	exp.i = 0;
	exp.isexpandable = 0;
	exp.single_quote = 0;
	exp.double_quote = 0;
	while (input_str[exp.i] != '\0')
	{
		if (input_str[exp.i] == '\'' && exp.double_quote == 0)
		{
			exp.single_quote = 1;
			exp.double_quote = 0;
		}
		if (input_str[exp.i] == '\"' && exp.single_quote == 0)
		{
			exp.double_quote = 1;
			exp.single_quote = 0;
		}
		if (input_str[exp.i] == '$' && !exp.double_quote && !exp.single_quote)
			return (1);
		if (input_str[exp.i] == '$' && exp.double_quote)
			exp.isexpandable = 1;
		exp.i++;
	}
	return (exp.isexpandable);
}

//expand_variables_in_tokens
void	concatenvtoken(t_data *shell_data)
{
	t_tokens	*current_token;

	current_token = shell_data->cmdchain;
	while (current_token)
	{
		if (can_expand_variables(current_token->content))
		{
			current_token->content = process_dollar_sign
				(current_token->content, shell_data);
		}
		current_token = current_token->next;
	}
}
