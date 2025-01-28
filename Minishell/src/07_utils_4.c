/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_utils_4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 11:50:41 by gfantoni          #+#    #+#             */
/*   Updated: 2024/06/18 11:51:18 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*mini_expand_with_invalid(t_mini *mini, char *sub_token)
{
	char	*str_joined;
	char	*str_expanded;
	char	*str_after_invalid;
	char	*str_before_invalid;

	if (mini_is_invalid_char(sub_token[1]))
		return (sub_token);
	str_after_invalid = mini_str_after_invalid_char(sub_token);
	str_before_invalid = mini_str_before_invalid_char(sub_token);
	str_expanded = mini_search_and_replace(mini, str_before_invalid);
	str_joined = ft_strjoin_expansion(str_expanded, str_after_invalid);
	ft_collect_mem(str_joined);
	return (str_joined);
}

int	mini_is_invalid_char(char c)
{
	if (c < 48
		|| (c > 57 && c < 65)
		|| (c > 90 && c < 95)
		|| (c > 95 && c < 97)
		|| c > 122)
		return (1);
	return (0);
}

char	*mini_str_after_invalid_char(char *sub_token)
{
	char	*str_after;
	int		i;

	str_after = ft_calloc(sizeof(char), ft_strlen(sub_token) + 1);
	ft_collect_mem(str_after);
	sub_token++;
	i = 0;
	while (*sub_token)
	{
		if (*sub_token < 48
			|| (*sub_token > 57 && *sub_token < 65)
			|| (*sub_token > 90 && *sub_token < 95)
			|| (*sub_token > 95 && *sub_token < 97)
			|| *sub_token > 122)
			break ;
		sub_token++;
	}
	i = 0;
	while (sub_token[i])
	{
		str_after[i] = sub_token[i];
		i++;
	}
	return (str_after);
}

char	*mini_str_before_invalid_char(char *sub_token)
{
	char	*str_before;
	int		i;

	str_before = ft_calloc(sizeof(char), ft_strlen(sub_token) + 1);
	ft_collect_mem(str_before);
	str_before[0] = '$';
	i = 1;
	while (sub_token[i])
	{
		if (sub_token[i] < 48
			|| (sub_token[i] > 57 && sub_token[i] < 65)
			|| (sub_token[i] > 90 && sub_token[i] < 95)
			|| (sub_token[i] > 95 && sub_token[i] < 97)
			|| sub_token[i] > 122)
			break ;
		str_before[i] = sub_token[i];
		i++;
	}
	return (str_before);
}

char	*ft_strjoin_expansion(char const *s1, char const *s2)
{
	char	*new;
	size_t	len;
	size_t	c;
	size_t	z;

	len = ft_strlen(s2);
	if (s1)
		len += ft_strlen(s1);
	new = (char *)ft_calloc(sizeof(char), (len + 1));
	c = 0;
	if (s1)
	{
		c = -1;
		while (s1[++c] != '\0')
			new[c] = s1[c];
	}
	z = 0;
	while (s2[z] != '\0')
		new[c++] = s2[z++];
	return (new);
}
