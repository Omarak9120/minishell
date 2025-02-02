/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_get_cmd_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:19:50 by oabdelka          #+#    #+#             */
/*   Updated: 2025/02/02 16:46:27 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/mini_get_cmd_path.h"

void	mini_get_cmd_exec_path(t_mini *mini)
{
	t_cmd	*cmd_exec_node;

	cmd_exec_node = mini->cmd_exec_list;
	while (cmd_exec_node)
	{
		if (cmd_exec_node->nbr_of_words && cmd_exec_node->cmd_exec[0])
			cmd_exec_node->cmd_path = mini_get_cmd_path(mini, cmd_exec_node);
		cmd_exec_node = cmd_exec_node->next;
	}
}

/*cmd_exec[0] = "echo" ---> "/bin/echo"*/
/*"/usr/local/bin:/usr/bin:/bin"
["/usr/local/bin", "/usr/bin", "/bin", NULL]
 *   Given a command node (with cmd_exec[0] as the command),
 *   decides how to resolve it to a full path. If the command
 *   starts with "./" or is empty, returns it unchanged. Otherwise,
 *   searches through the PATH environment variable directories:
 *   - Splits PATH by ':'.
 *   - Joins each directory with the command name.
 *   - If a valid executable is found (access == 0), returns that path.
 *   If nothing is found, returns the command name as-is.
 */

char	*mini_get_cmd_path(t_mini *mini, t_cmd *cmd_exec_node)
{
	t_get_cmd_path	tmp_struct;
	int				i;

	tmp_struct.cmd_name = cmd_exec_node->cmd_exec[0];
	if ((tmp_struct.cmd_name[0] == '.' && tmp_struct.cmd_name[1] == '/')
		|| tmp_struct.cmd_name[0] == '\0')
		return (tmp_struct.cmd_name);
	tmp_struct.path = mini_search_in_envlist(mini, "PATH");
	tmp_struct.splited_path = ft_split(tmp_struct.path, ':');
	i = 0;
	while (tmp_struct.splited_path && tmp_struct.splited_path[i])
	{
		tmp_struct.part_path = ft_strjoin(tmp_struct.splited_path[i], "/");
		tmp_struct.path = ft_strjoin(tmp_struct.part_path, tmp_struct.cmd_name);
		ft_collect_mem(tmp_struct.path);
		free(tmp_struct.part_path);
		if (access(tmp_struct.path, F_OK) == 0)
		{
			free_split(tmp_struct.splited_path);
			return (tmp_struct.path);
		}
		i++;
	}
	free_split(tmp_struct.splited_path);
	return (tmp_struct.cmd_name);
}

char	*mini_search_in_envlist(t_mini *mini, char *key)
{
	char	*value;
	t_dict	*cur;

	value = NULL;
	cur = mini->env_list;
	while (cur)
	{
		if (!ft_strncmp(cur->key, key, ft_strlen(cur->key) + ft_strlen(key)))
			value = cur->value;
		cur = cur->next;
	}
	return (value);
}
