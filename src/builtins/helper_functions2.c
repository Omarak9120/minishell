/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjamil <mjamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:50:05 by mjamil            #+#    #+#             */
/*   Updated: 2024/09/25 13:50:05 by mjamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ft_perror(const char *msg)
{
    if (msg)
        fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    else
        fprintf(stderr, "%s\n", strerror(errno));
}

void *ft_realloc(void *ptr, size_t original_size, size_t new_size)
{
    if (new_size == 0)
    {
        free(ptr);
        return NULL;
    }
    if (!ptr)
        return malloc(new_size);
    void *new_ptr = malloc(new_size);
    if (!new_ptr)
        return NULL;
    size_t copy_size = original_size < new_size ? original_size : new_size;
    ft_memcpy(new_ptr, ptr, copy_size);
    free(ptr);

    return new_ptr;
}