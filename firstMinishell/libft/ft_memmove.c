/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 10:56:58 by oabdelka          #+#    #+#             */
/*   Updated: 2024/08/07 10:56:59 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const unsigned char	*sp;
	unsigned char		*dp;

	sp = (const unsigned char *)src;
	dp = (unsigned char *)dest;
	if (dest == src)
		return (dest);
	if (dp > sp && dp < (n + sp))
	{
		while (n--)
		{
			*(dp + n) = *(sp + n);
		}
	}
	else
	{
		while (n--)
		{
			*dp = *sp;
			dp++;
			sp++;
		}
	}
	return (dest);
}
