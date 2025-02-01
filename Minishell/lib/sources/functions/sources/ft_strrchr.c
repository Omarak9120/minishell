/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:05:29 by oabdelka          #+#    #+#             */
/*   Updated: 2025/02/01 19:05:30 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*alts;
	size_t	len;

	alts = (char *)s;
	len = ft_strlen(s);
	if (c == '\0')
		return (alts + len);
	while (len != 0)
	{
		if (alts[len] == (char)c)
			return (alts + len);
		len--;
	}
	if (s[0] == (char)c)
		return (alts);
	return (0);
}
