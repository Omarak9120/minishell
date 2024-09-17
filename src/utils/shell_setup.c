/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksayour <ksayour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:26:55 by ksayour           #+#    #+#             */
/*   Updated: 2024/09/17 14:28:56 by ksayour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char **copy_environment() {
    extern char **environ;
    int i = 0;
    while (environ[i])
        i++;

    char **env_copy = malloc(sizeof(char *) * (i + 1));
    for (int j = 0; j < i; j++) {
        env_copy[j] = strdup(environ[j]);  // Duplicate each environment string
    }
    env_copy[i] = NULL;
    return env_copy;
}

void free_environment(char **env) {
    for (int i = 0; env[i]; i++) {
        free(env[i]);
    }
    free(env);
}

// Function to initialize the shell
void setup_shell(t_data *data) {
    // Set up the environment variables
    data->env = copy_environment();  // A function that duplicates the current env
    
    // Initialize signals
    signal(SIGINT, handle_sigint);   // Handle Ctrl+C
    signal(SIGQUIT, SIG_IGN);        // Ignore Ctrl+\ (SIGQUIT)
}

// Function to clean up resources before exiting
void cleanup_shell(t_data *data) {
    // Free the environment variables if necessary
    free_environment(data->env);     // Assuming a function exists to free env
}