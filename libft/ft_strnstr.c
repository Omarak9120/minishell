/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 10:58:10 by oabdelka          #+#    #+#             */
/*   Updated: 2024/08/07 10:58:11 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	lenlittle;
	size_t	i;
	size_t	j;

	i = 0;
	lenlittle = ft_strlen (little);
	if (lenlittle == 0 || little == big)
		return ((char *)big);
	while (big[i] != '\0' && i < len)
	{
		j = 0;
		while (((j + i) < len) && little[j] != '\0'
			&& big[i + j] != '\0' && big[i + j] == little[j])
		{
			j++;
			if (j == lenlittle)
				return ((char *)big + i);
		}
		i++;
	}
	return (0);
}
