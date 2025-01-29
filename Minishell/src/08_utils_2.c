/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:24:16 by oabdelka          #+#    #+#             */
/*   Updated: 2025/01/29 18:34:27 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmd	*mini_redir_lstnew(void)
{
	t_cmd	*new_node;

	new_node = malloc(sizeof(t_cmd));
	if (new_node == NULL)
		return (NULL);
	new_node->input_fd = 0;
	new_node->output_fd = 1;
	new_node->read_pipe = -1;
	new_node->write_pipe = -1;
	new_node->nbr_of_words = 0;
	new_node->cmd_exec = NULL;
	new_node->cmd_path = NULL;
	new_node->next = NULL;
	new_node->pid = -1;
	ft_collect_mem(new_node);
	return (new_node);
}

void	mini_redir_lstadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*last_node;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last_node = mini_redir_lstlast(*lst);
	last_node->next = new;
}

t_cmd	*mini_redir_lstlast(t_cmd *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
/*
#include "../include/minishell.h"

t_cmd    *mini_redir_lstnew(void)
{
    t_cmd    *new_node;

    new_node = ft_calloc(1, sizeof(t_cmd));
    if (!new_node)
        return NULL;
    new_node->input_fd = STDIN_FILENO;
    new_node->output_fd = STDOUT_FILENO;
    new_node->read_pipe = -1;
    new_node->write_pipe = -1;
    new_node->pid = -1;
    ft_collect_mem(new_node);
    return new_node;
}

void    mini_redir_lstadd_back(t_cmd **lst, t_cmd *new)
{
    t_cmd    *last;

    if (!*lst) {
        *lst = new;
        return;
    }
    last = *lst;
    while (last->next)
        last = last->next;
    last->next = new;
}

void    mini_redir_lstdelone(t_cmd *node)
{
    if (!node)
        return;
    if (node->input_fd > 2)
        close(node->input_fd);
    if (node->output_fd > 2)
        close(node->output_fd);
    free(node->cmd_exec);
    free(node->cmd_path);
    free(node);
}*/