/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksayour <ksayour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:56:23 by oabdelka          #+#    #+#             */
/*   Updated: 2024/09/12 12:49:22 by ksayour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <readline/readline.h>
# include <readline/history.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// Handler for SIGINT (Ctrl + C)
void handle_sigint(int sig) {
    (void)sig;
    write(1, "\nTRY AGAIN! ", 12); // Mimic bash's behavior by showing the prompt again
}

// Handler for SIGQUIT (Ctrl + \)
void handle_sigquit(int sig) {
    (void)sig;
    write(1, "Quit: 3\n", 8);
}

// Function to handle Ctrl + D
void handle_ctrl_d() {
    write(1, "exit\n", 5);
    exit(0); // Exit the minishell
}

int main() {
    char    *input;
    char *line = NULL;
    size_t len = 0;

    // Set signal handlers
    signal(SIGINT, handle_sigint);   // Ctrl + C
    signal(SIGQUIT, handle_sigquit); // Ctrl + \
    
    while (1) {
        input = readline("minishell> ");
        if (!input)
            break;  // Handle EOF (Ctrl+D)
        
        if (input[0] != '\0')
            add_history(input);  // Add input to history

        // Display the prompt
        // write(1, "minishell$ ", 11);

        // Get user input
        if (getline(&line, &len, stdin) == -1) {
            // If Ctrl + D is pressed (EOF), handle it
            if (feof(stdin)) {
                handle_ctrl_d();
            }
        }

        // Your command processing logic here
    }

    free(line);
    return 0;
}
