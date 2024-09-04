/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:56:13 by oabdelka          #+#    #+#             */
/*   Updated: 2024/09/04 14:59:49 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int main() {
    char *input;
    char **args;

    signal(SIGINT, handle_signal);  // Handle Ctrl+C

    while (1) {
        input = readline("minishell> ");
        if (!input)
            break;  // Handle EOF (Ctrl+D)
        
        if (input[0] != '\0')
            add_history(input);  // Add input to history

        args = parse(input);  // Parse the input into tokens
        
        if (args[0])
            execute(args);  // Execute the parsed command

        free(input);
        free(args);
    }
    return 0;
}
