/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjamil <mjamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:28:41 by mjamil            #+#    #+#             */
/*   Updated: 2024/09/14 20:28:41 by mjamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>

int         builtin_unset(t_data *data, char **args)
{
    (void)data;
    (void)args;
    return (0);
}
//     if (var == NULL) {
//         printf("Usage: unset VAR\n");
//         return;
//     }

//     // Use unsetenv to remove the variable from the environment
//     if (unsetenv(var) != 0) {
//         perror("unsetenv");
//     } else {
//         printf("Unset: %s\n", var);
//     }
// }
