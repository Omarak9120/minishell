/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trashman_env.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:55:10 by oabdelka          #+#    #+#             */
/*   Updated: 2025/02/01 19:55:13 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRASHMAN_ENV_H
# define TRASHMAN_ENV_H

# include "../lib/includes/libft.h"

t_list	**ft_get_mem_addresss_env(void);
void	ft_collect_mem_env(void *content);
void	ft_trashman_env(t_list **lst_memory);
t_dict	*ft_dictnew_env(char **var);

#endif