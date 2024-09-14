/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjamil <mjamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:31:24 by mjamil            #+#    #+#             */
/*   Updated: 2024/09/14 20:31:24 by mjamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void env_command(t_data *data) {
    if (data == NULL || data->env == NULL) {
        printf("Error: No environment context available.\n");
        return;
    }

    char **env = data->env; // Use the environment variables from the struct

    // Iterate through the environment variables and print each one
    while (*env) {
        printf("%s\n", *env);
        env++;
    }
}