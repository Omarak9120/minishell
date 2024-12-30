/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjamil <mjamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 17:50:59 by mjamil            #+#    #+#             */
/*   Updated: 2024/12/30 17:50:59 by mjamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//allocate_env_variable
t_env *create_envp_node(char *key, char *value, int hidden)
{
    t_env *new_node;

    new_node = (t_env *)malloc(sizeof(t_env));
    if (!new_node)
        return (NULL);
    new_node->key = ft_strdup(key);
    new_node->value = ft_strdup(value);
    new_node->hidden = hidden;
    new_node->next = NULL;

    return (new_node);
}

//parse_and_create_env_node
t_env *create_envp_list_node(char *envp_str, int hidden)
{
    char *key;
    char *value;
    t_env *new_node;

    ft_split_env(envp_str, &key, &value);
    new_node = create_envp_node(key, value, hidden);
    free(key);
    free(value);

    return (new_node);
}

//append_env_node
void add_node_to_envp_list(t_env **head, t_env **current, t_env *new_node)
{
    if (!*head)
        *head = new_node;
    else
        (*current)->next = new_node;
    *current = new_node;
}

//initialize_env_list
t_env *init_copy_envp(char **envp)
{
    t_env *head = NULL;
    t_env *current = NULL;
    t_env *new_node;
    char *char_uid;
    pid_t uid;

    uid = ft_getuid();
    char_uid = ft_itoa((int)uid);
    while (*envp)
    {
        new_node = create_envp_list_node(*envp, 0);
        if (!new_node)
        {
            free_env_list(head);
            free(char_uid);
            return (NULL);
        }
        add_node_to_envp_list(&head, &current, new_node);
        envp++;
    }
    if (set_env(&head, "UID", char_uid, 0) != 0)
    {
        free_env_list(head);
        free(char_uid);
        return (NULL);
    }
    free(char_uid);
    return (head);
}
