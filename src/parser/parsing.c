/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:56:28 by oabdelka          #+#    #+#             */
/*   Updated: 2024/09/04 14:56:29 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"


char **parse(char *input) {
    char **tokens = malloc(sizeof(char*) * 64);  // Example size
    char *token = strtok(input, " ");
    int i = 0;

    while (token) {
        tokens[i++] = token;
        token = strtok(NULL, " ");
    }
    tokens[i] = NULL;
    return tokens;
}
