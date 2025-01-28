/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr_mem.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:01:36 by josfelip          #+#    #+#             */
/*   Updated: 2024/06/17 12:27:24 by josfelip         ###   ########.fr       */
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
