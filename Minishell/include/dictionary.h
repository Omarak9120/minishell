/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:54:28 by oabdelka          #+#    #+#             */
/*   Updated: 2025/02/01 19:54:29 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DICTIONARY_H
# define DICTIONARY_H

# include "../lib/includes/libft.h"

typedef struct s_dict
{
	char			*key;
	char			*value;
	struct s_dict	*next;
}				t_dict;

t_dict	*ft_dictnew(char **var);
t_dict	*ft_dictlast(t_dict *dict);
t_dict	*ft_dictsort(t_dict *dict);
void	ft_dictadd_back(t_dict **dict, t_dict *new_entry);
void	ft_dict_insert(t_dict **dict, char **var);
void	ft_dict_print(t_dict *dict);
int		ft_dict_update(t_dict *dict, char **var);
int		ft_dictdel_entry(t_dict **dict, char *name);
size_t	ft_max(size_t a, size_t b);
char	*ft_dict_get_value(t_dict *dict, char *key);

#endif