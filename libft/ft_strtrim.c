/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 10:58:19 by oabdelka          #+#    #+#             */
/*   Updated: 2024/08/07 10:58:21 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int	start;
	int	end;

	start = 0;
	end = ft_strlen(s1);
	if (!s1)
		return (ft_strdup(""));
	if (!set)
		return (ft_strdup(s1));
	while (is_set(s1[start], set))
		start++;
	if (start == end)
		return (ft_strdup(""));
	while (is_set(s1[end - 1], set))
		end--;
	return (ft_substr(s1, start, end - start));
}
