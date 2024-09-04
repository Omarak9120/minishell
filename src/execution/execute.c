/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:56:30 by oabdelka          #+#    #+#             */
/*   Updated: 2024/09/04 14:56:31 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"


void execute(char **args) {
    pid_t pid = fork();
    
    if (pid == 0) {  // Child process
        if (execve(args[0], args, NULL) == -1) {
            perror("minishell");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {  // Fork failed
        perror("minishell");
    } else {  // Parent process
        waitpid(pid, NULL, 0);
    }
}
