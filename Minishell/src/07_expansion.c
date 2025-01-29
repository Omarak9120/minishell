/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:56:46 by josfelip          #+#    #+#             */
/*   Updated: 2025/01/29 13:50:16 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	mini_expansion(t_mini *mini)
{
	int		i;
	t_token	*cmd;

	i = 0;
	cmd = mini->commands[i];
	while (cmd)
	{
		mini_token_expansion(mini, i);
		i++;
		cmd = mini->commands[i];
	}
}

void	mini_token_expansion(t_mini *mini, int i)
{
	t_token	*token_node;

	token_node = mini->commands[i];
	while (token_node)
	{
		if (ft_strchr(token_node->token, '$') && !token_node->was_squoted)
		{
			token_node->token = mini_sep_exp_join(mini, token_node->token);
			mini_find_space(mini, i);
		}
		token_node = token_node->next;
	}
}

char	*mini_sep_exp_join(t_mini *mini, char *token)
{
	t_sub_token	*sub_token_lst;
	t_sub_token	*current;
	char		*sub_token;

	sub_token_lst = NULL;
	mini_sub_tokenizier(token, &sub_token_lst, 0, 0);
	current = sub_token_lst;
	while (current)
	{
		sub_token = current->content;
		if (sub_token[0] == '$' && sub_token[1])
			current->content = mini_search_and_replace(mini, sub_token);
		current = current->next;
	}
	return (mini_sub_token_join(sub_token_lst));
}

char	*mini_search_and_replace(t_mini *mini, char *sub_token)
{
	t_dict	*current;
	char	*new_sub_token;

	if (sub_token[1] == '?')
		return (mini_get_dollar_sign(mini, sub_token));
	// if (sub_token[1] == '@' || sub_token[1] == '*')
	// {
	// 	char* omar = ft_strdup("");
	// 	ft_collect_mem(omar);
	// 	return (omar);}
	if (mini_has_invalid_char(sub_token))
		return (mini_expand_with_invalid(mini, sub_token));
	current = mini->env_list;
	sub_token++;//Skip the $
	new_sub_token = NULL;
	while (current)//Loop over mini->env_list (KEY=VALUE) to find a key that matches sub_token
	{
		if (!ft_strncmp(current->key, sub_token, ft_strlen(sub_token)))
		{
			new_sub_token = current->value;
			break ;
		}
		current = current->next;
	}
	return (new_sub_token);
}
/* after the $ sign [0-9A-Za-z_????]*/
int		mini_has_invalid_char(char *sub_token)
{
	int	i;

	sub_token++;
	i = 0;
	while (sub_token[i])
	{
		if (sub_token[i] < 48
			|| (sub_token[i] > 57 && sub_token[i] < 65)
			|| (sub_token[i] > 90 && sub_token[i] < 95)
			|| (sub_token[i] > 95 && sub_token[i] < 97)
			|| sub_token[i] > 122)
			return (1);
		i++;
	}
	return (0);
}
/*
  if (isdigit(sub_token[1]))
        return (expand_digit_param(mini, sub_token));

  char *expand_digit_param(t_mini *mini, char *sub_token)
{
    // sub_token looks like "$123" or "$1abc" etc.
    char *p = sub_token + 1; // skip '$'

    // Extract the FIRST digit as the param number:
    int param_num = (*p - '0'); 
    p++; // move past that one digit

    // Expand that param
    char *expanded = get_positional_param(mini, param_num); 
    // e.g., if param_num=1 => returns the string in $1, or "" if unset

    // leftover digits (and letters) are appended literally
    // e.g. if sub_token was "$123" => we've used '1', leftover is "23"
    char *result = ft_strjoin_expansion(expanded, p);
    ft_collect_mem(result);
    return result;
}
   char *get_positional_param(t_mini *mini, int param_num)
{
    // If you don't store shell arguments, always return empty:
    // or use your actual logic if you do store them.
    char *empty = ft_strdup("");
    ft_collect_mem(empty);
    return empty;
}
*/
