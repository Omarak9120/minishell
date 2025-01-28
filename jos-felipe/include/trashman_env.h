
#ifndef TRASHMAN_ENV_H
# define TRASHMAN_ENV_H

# include "../lib/includes/libft.h"

t_list	**ft_get_mem_address_env(void);
void	ft_collect_mem_env(void *content);
void	ft_free_trashman_env(t_list **lst_memory);
t_dict	*ft_dictnew_env(char **var);

#endif