#ifndef BUILTINS_H
# define BUILTINS_H

# include "../include/minishell.h"

int		mini_env(t_token *arg, t_dict **dict);
int		mini_pwd(void);
void	mini_exit(t_token *arg, int status_last_cmd);

#endif
