#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

void execute(char **args);
int cd_command(char **args);
char **parse(char *input);
void handle_signal(int signum);

#endif
