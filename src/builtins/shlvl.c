/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjamil <mjamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 03:30:44 by mjamil            #+#    #+#             */
/*   Updated: 2024/10/03 03:30:44 by mjamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void update_shlvl(t_data *data) {
    int i = 0;
    int current_shlvl = 1;
    char *shlvl = NULL;
    while (data->env[i] != NULL) {
        if (ft_strncmp(data->env[i], "SHLVL=", 6) == 0) {
            shlvl = data->env[i] + 6;
            current_shlvl = ft_atoi(shlvl);
            current_shlvl++;
            break;
        }
        i++;
    }

    char new_shlvl[16];
    snprintf(new_shlvl, sizeof(new_shlvl), "%d", current_shlvl);
    setenv("SHLVL", new_shlvl, 1);
    if (shlvl) {
        free(data->env[i]);
        char new_shlvl_str[25];
        snprintf(new_shlvl_str, sizeof(new_shlvl_str), "SHLVL=%s", new_shlvl);
        data->env[i] = ft_strdup(new_shlvl_str);
    }
}