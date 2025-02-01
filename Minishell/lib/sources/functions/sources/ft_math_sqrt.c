/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math_sqrt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:03:46 by oabdelka          #+#    #+#             */
/*   Updated: 2025/02/01 19:03:47 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

long	ft_math_sqrt(long nb, long kick)
{
	long	result;

	if (nb > 0)
	{
		while (1)
		{
			result = (kick + (nb / kick)) / 2;
			if (result == kick)
			{
				if (result * result == nb)
					return (result);
				else
					return (0);
			}
			kick = result;
		}
	}
	return (0);
}
