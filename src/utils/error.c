/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksayour <ksayour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:45:13 by ksayour           #+#    #+#             */
/*   Updated: 2024/09/17 14:46:27 by ksayour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

void print_error(char *msg, int exit_code) {
    // Print the error message to stderr
    fprintf(stderr, "Error: %s\n", msg);

    // If an exit code is provided, exit the program with that code
    if (exit_code != 0) {
        exit(exit_code);
    }
}
