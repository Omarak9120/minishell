/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjamil <mjamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 15:49:17 by mjamil            #+#    #+#             */
/*   Updated: 2024/12/30 15:49:17 by mjamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//process_env_variable
void	handle_normal_variable(char *input, int *i, char **result, t_env *env)
{
	int		start;
	int		end;
	char	*sub_env;
	char	*env_value;

	(*i)++;
	start = *i;
	while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_'))
		(*i)++;
	end = *i;
	if (start != end)
	{
		sub_env = ft_substr(input, start, end - start);
		env_value = get_env(env, sub_env);
		if (env_value)
			*result = ft_strjoingnl(*result, env_value);
		free(env_value);
		free(sub_env);
	}
	else
		*result = ft_strjoingnl(*result, "$");
}

//process_double_dollar
void	handle_two_dollar(char **result, int *i)
{
	char	*num_str;

	num_str = ft_itoa(getpid());
	*result = ft_strjoingnl(*result, num_str);
	*i += 2;
	free(num_str);
}

//process_exit_status
void	handle_question_mark(char **result, int *i, t_data *data)
{
	char	*out;

	out = ft_itoa(data->cmd.status);
	*result = ft_strjoingnl(*result, out);
	free(out);
	(*i) += 2;
}

//append_single_char
void	copy_and_append_char(char **result, char *input, int *i)
{
	char	tmp[2];

	tmp[0] = input[*i];
	tmp[1] = '\0';
	*result = ft_strjoingnl(*result, tmp);
	(*i)++;
}

//expand_dollar_variables
char	*handle_dollar_sign(char *input, t_data *data)
{
	int		i;
	char	*result;

	i = 0;
	result = ft_strdup("");
	while (i < ft_strlen1(input) && input[i])
	{
		if (input[i] == '$' && isquote(input[i + 1]) && i == 0)
			i++;
		else if (input[i] == '$')
		{
			if (input[i + 1] == '$')
				handle_two_dollar(&result, &i);
			else if (input[i + 1] == '?')
				handle_question_mark(&result, &i, data);
			else if (ft_isdigit(input[i + 1]))
				i += 2;
			else
				handle_normal_variable(input, &i, &result, data->env_list);
		}
		else
			copy_and_append_char(&result, input, &i);
	}
	free(input);
	return (result);
}
