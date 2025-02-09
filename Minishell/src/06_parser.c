/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:08:44 by oabdelka          #+#    #+#             */
/*   Updated: 2025/02/04 17:41:43 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * Parses the `token_list` into separate commands based on pipes.
 * It first counts the number of commands, allocates an array to hold them, 
 * and then populates this array with token lists for each command.
 */

void	parser(t_mini *mini)
{
	int		nbr_cmds;

	nbr_cmds = 0;
	if (mini->token_list)
	{
		nbr_cmds = mini_count_nbr_pipes(mini->token_list) + 1;
		mini->commands = (t_token **)ft_calloc(sizeof(t_token *), nbr_cmds + 1);
		ft_collect_mem(mini->commands);
		mini_fill_cmd_array(mini);
	}
}
/**
 * Counts the number of pipes (`|`) in the `token_list`.
 * This determines the number of commands in the input.
 * Returns the number of pipes found.
 */

int	mini_count_nbr_pipes(t_token *token_list)
{
	t_token	*temp;
	int		nbr_pipes;

	temp = token_list;
	nbr_pipes = 0;
	while (temp)
	{
		if (!ft_strncmp(temp->token, "|", 2))
			nbr_pipes++;
		temp = temp->next;
	}
	return (nbr_pipes);
}
/**
 * Fills the `mini->commands` array with token lists for each command.
 * Splits the `token_list` into separate linked lists of tokens for each command,
 * using the pipe (`|`) symbol as the delimiter.
 */

void	mini_fill_cmd_array(t_mini *mini)
{
	t_token	*current;
	t_token	*new;
	char	*token;
	int		i;

	new = NULL;
	i = 0;
	current = mini->token_list;
	while (current)
	{
		token = current->token;
		if (!ft_strncmp(token, "|", 2))
		{
			mini->commands[i] = new;
			new = NULL;
			i++;
		}
		else
			mini_token_lstadd_back(&new, mini_t_token_dup(current));
		current = current->next;
	}
	mini->commands[i] = new;
}
/**
 * Duplicates a `t_token` node, creating a new node with the same content.
 * This ensures that modifications to one list do not affect the other.
 * Returns the duplicated `t_token` node.
 */

t_token	*mini_t_token_dup(t_token *t)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	if (new_node == NULL)
		return (NULL);
	new_node->token = t->token;
	new_node->gender = t->gender;
	new_node->specie = t->specie;
	new_node->was_quoted = t->was_quoted;
	new_node->was_squoted = t->was_squoted;
	new_node->next = NULL;
	new_node->prev = NULL;
	ft_collect_mem(new_node);
	return (new_node);
}
/*
Input: echo hello | grep h | wc -l
commands[0]: Tokens for echo hello
commands[1]: Tokens for grep h
commands[2]: Tokens for wc -l

For echo hello | grep h | wc -l, 
the function would return 2.


input token_list (linked list): 
echo -> hello -> | -> grep -> h -> | -> wc -> -l
Output commands (array of linked lists):
commands[0]: echo -> hello
commands[1]: grep -> h
commands[2]: wc -> -l
*/