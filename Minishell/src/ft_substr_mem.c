/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr_mem.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:10:54 by oabdelka          #+#    #+#             */
/*   Updated: 2025/02/01 19:10:55 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libftplus.h"

char	*ft_substr_mem(char *str, int start, int len)
{
	char	*sub;

	sub = ft_substr(str, start, len);
	ft_collect_mem(sub);
	return (sub);
}
