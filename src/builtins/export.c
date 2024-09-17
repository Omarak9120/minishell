/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjamil <mjamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:47:11 by mjamil            #+#    #+#             */
/*   Updated: 2024/09/14 19:47:11 by mjamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

int         builtin_export(t_data *data, char **args)
{
    (void)data;
    (void)args;
    return (0);
    // if (var == NULL || value == NULL) {
    //     printf("Usage: export VAR=value\n");
    //     return;
    // }

    // // Create the variable in the format "VAR=value"
    // char *env_var = malloc(strlen(var) + strlen(value) + 2); // +2 for '=' and '\0'
    // if (env_var == NULL) {
    //     perror("malloc");
    //     return;
    // }
    
    // sprintf(env_var, "%s=%s", var, value);
    
    // // Use putenv or setenv to export the variable
    // if (putenv(env_var) != 0) {
    //     perror("putenv");
    // } else {
    //     printf("Exported: %s\n", env_var);
    // }
    
    // No need to free env_var because putenv uses it directly
}
