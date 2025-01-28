/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math_sqrt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:07:22 by gfantoni          #+#    #+#             */
/*   Updated: 2024/02/23 19:01:14 by josfelip         ###   ########.fr       */
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
