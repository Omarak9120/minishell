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

#include <stdio.h>
#include <stdlib.h>

void my_unset(const char *var) {
    if (var == NULL) {
        printf("Usage: unset VAR\n");
        return;
    }

    // Use unsetenv to remove the variable from the environment
    if (unsetenv(var) != 0) {
        perror("unsetenv");
    } else {
        printf("Unset: %s\n", var);
    }
}
