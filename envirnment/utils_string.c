/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjamil <mjamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 20:20:56 by mjamil            #+#    #+#             */
/*   Updated: 2024/12/30 20:20:56 by mjamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//get_str_length
size_t	ft_strnlen(const char *str, size_t max_len)
{
	size_t	len;

	len = 0;
	while (len < max_len && str[len] != '\0')
		len++;
	return (len);
}

//copy_string
char	*ft_strncpy(char *destination, const char *source, size_t max_len)
{
	size_t	index;

	index = 0;
	while (index < max_len)
	{
		if (source[index] != '\0')
			destination[index] = source[index];
		else
			destination[index] = '\0';
		index++;
	}
	return (destination);
}

//duplicate_string
char	*ft_strndup(const char *source, size_t max_len)
{
	size_t	length;
	char	*copy;

	*copy = malloc(length + 1);
	length = get_str_length(source, max_len);
	if (!copy)
		return (NULL);
	copy_string(copy, source, length);
	copy[length] = '\0';
	return (copy);
}

//compute_string_length
int	ft_strlen1(const char *str)
{
	int	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

//split_env_variable
void	split_envp(char *env_var, char **key, char **value)
{
	char	*separator;

	*separator = strchr(env_var, '=');
	if (separator)
	{
		*key = duplicate_string(env_var, separator - env_var);
		*value = strdup(separator + 1);
	}
	else
	{
		*key = strdup(env_var);
		*value = NULL;
	}
}
