/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 10:57:42 by oabdelka          #+#    #+#             */
/*   Updated: 2024/08/07 10:57:43 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t			len;
	int				i;
	char			*s;

	len = ft_strlen (s1) + ft_strlen (s2);
	s = ft_calloc((len + 1), sizeof (char));
	if (!s)
		return (NULL);
	len = 0;
	while (s1[len])
	{
		s[len] = s1[len];
		len++;
	}
	i = 0;
	while (s2[i])
	{
		s[i + len] = s2[i];
		i++;
	}
	s[ft_strlen (s1) + ft_strlen (s2)] = '\0';
	return (s);
}
