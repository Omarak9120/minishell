/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:56:23 by oabdelka          #+#    #+#             */
/*   Updated: 2024/09/04 14:56:24 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "includes/minishell.h"

void handle_signal(int signum) {
    if (signum == SIGINT) {
        printf("\nminishell> ");
        fflush(stdout);
    }
}