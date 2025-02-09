/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:54:20 by oabdelka          #+#    #+#             */
/*   Updated: 2025/02/01 19:57:12 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../include/minishell.h"

int			env(t_token *arg, t_dict **dict);
int			pwd(void);
int			mini_exit(t_token *args, int last_status, t_mini *mini);
long		ft_atol(const char *str);
int			is_valid_number(char *str);
void		clean_exit(t_mini *mini, int status);

#endif
