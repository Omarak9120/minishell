/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjamil <mjamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 12:56:09 by mjamil            #+#    #+#             */
/*   Updated: 2024/09/23 13:03:48 by mjamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *my_getenv(char **env, const char *name)
{
    size_t len = strlen(name);

    for (int i = 0; env[i] != NULL; i++)
    {
        if (strncmp(env[i], name, len) == 0 && env[i][len] == '=')
        {
            printf("Found %s=%s\n", env[i], &env[i][len + 1]);
            return &env[i][len + 1];
        }
    }
    printf("Variable %s not found\n", name);
    return NULL;
}
char *my_strcpy(char *dest, const char *src)
{
    int i = 0;
    while (src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}
int my_strcmp(const char *s1, const char *s2)
{
    int i = 0;

    while (s1[i] != '\0' && s2[i] != '\0')
    {
        if (s1[i] != s2[i])
        {
            return (unsigned char)s1[i] - (unsigned char)s2[i];
        }
        i++;
    }
    return (unsigned char)s1[i] - (unsigned char)s2[i];
}
char *my_strcat(char *dest, const char *src)
{
    int i = 0;
    int j = 0;

    while (dest[i] != '\0')
        i++;
    while (src[j] != '\0')
    {
        dest[i] = src[j];
        i++;
        j++;
    }
    dest[i] = '\0';
    return dest;
}
char *my_strncpy(char *dest, const char *src, size_t n)
{
    size_t i;

    i = 0;
    while (i < n && src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    while (i < n)
    {
        dest[i] = '\0';
        i++;
    }
    return dest;
}
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
    memcpy(new_ptr, ptr, copy_size);
    free(ptr);

    return new_ptr;
}