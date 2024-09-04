/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 10:58:16 by oabdelka          #+#    #+#             */
/*   Updated: 2024/08/07 10:58:17 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t			i;
	char			*str;
	unsigned char	ch;

	ch = (unsigned char )c;
	str = (char *)s;
	i = ft_strlen(s);
	if (ch == 0)
		return (str + i++);
	while (i > 0)
	{
		if (str[i] == ch)
			return (&str[i]);
		i--;
	}
	if (str[0] == ch)
		return (&str[0]);
	return (NULL);
}
