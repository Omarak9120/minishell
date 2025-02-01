/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trashman.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:55:17 by oabdelka          #+#    #+#             */
/*   Updated: 2025/02/01 19:55:20 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRASHMAN_H
# define TRASHMAN_H

# include "../lib/includes/libft.h"

t_list	**ft_get_mem_address(void);
void	ft_collect_mem(void *content);
void	ft_free_trashman(t_list **lst_memory);

#endif