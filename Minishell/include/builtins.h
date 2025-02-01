#ifndef BUILTINS_H
# define BUILTINS_H

# include "../include/minishell.h"

int		mini_env(t_token *arg, t_dict **dict);
int		mini_pwd(void);
// void	mini_exit(t_token *arg, int status_last_cmd);
void		mini_exit(t_token *args, int last_status, t_mini *mini);
long	    ft_atol(const char *str);
int         is_valid_number(char *str);
void	    exit_clean(t_mini *mini, int status);

#endif
