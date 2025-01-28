/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_utils_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantoni <gfantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:30:59 by gfantoni          #+#    #+#             */
/*   Updated: 2024/06/17 13:27:01 by gfantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	mini_is_dir(char *file)
{
	if (file[0] == '.' && file[1] == '\0')
		return (1);
	if (file[0] == '/')
		return (1);
	return (0);
}

void	mini_handle_out_redir(t_cmd *redir_node, char *file)
{
	int	fd;

	if (redir_node->input_fd < 0 || redir_node->output_fd < 0)
		return ;
	if (redir_node->output_fd != 1)
		close(redir_node->output_fd);
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 420);
	if (fd < 0 && access(file, F_OK))
		ft_printf_fd(STDERR_FILENO,
			"minishell: %s: No such file or directory\n", file);
	else if (fd < 0 && mini_is_dir(file))
		ft_printf_fd(STDERR_FILENO, "minishell: %s: Is a directory\n", file);
	else if (fd < 0 && access(file, W_OK))
		ft_printf_fd(STDERR_FILENO, "minishell: %s: Permission denied\n", file);
	redir_node->output_fd = fd;
}

void	mini_handle_in_redir(t_cmd *redir_node, char *file)
{
	int	fd;

	if (redir_node->input_fd < 0 || redir_node->output_fd < 0)
		return ;
	if (redir_node->input_fd != 0)
		close(redir_node->input_fd);
	fd = open(file, O_RDONLY);
	if (fd < 0 && access(file, F_OK))
		ft_printf_fd(STDERR_FILENO,
			"minishell: %s: No such file or directory\n", file);
	else if (fd < 0 && mini_is_dir(file))
		ft_printf_fd(STDERR_FILENO, "minishell: %s: Is a directory\n", file);
	else if (fd < 0 && access(file, R_OK))
		ft_printf_fd(STDERR_FILENO, "minishell: %s: Permission denied\n", file);
	redir_node->input_fd = fd;
}

void	mini_handle_append_redir(t_cmd *redir_node, char *file)
{
	int	fd;

	if (redir_node->input_fd < 0 || redir_node->output_fd < 0)
		return ;
	if (redir_node->output_fd != 1)
		close(redir_node->output_fd);
	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 420);
	if (fd < 0 && access(file, F_OK))
		ft_printf_fd(STDERR_FILENO,
			"minishell: %s: No such file or directory\n", file);
	else if (fd < 0 && mini_is_dir(file))
		ft_printf_fd(STDERR_FILENO, "minishell: %s: Is a directory\n", file);
	else if (fd < 0 && access(file, W_OK))
		ft_printf_fd(STDERR_FILENO, "minishell: %s: Permission denied\n", file);
	redir_node->output_fd = fd;
}

void	mini_handle_heredoc_redir(t_cmd *redir_node, char *file)
{
	int	fd;

	if (redir_node->input_fd < 0 || redir_node->output_fd < 0)
		return ;
	if (redir_node->input_fd != 0)
		close(redir_node->input_fd);
	fd = open(file, O_RDONLY);
	unlink(file);
	if (fd < 0 && access(file, F_OK))
		ft_printf_fd(STDERR_FILENO,
			"minishell: %s: No such file or directory\n", file);
	else if (fd < 0 && mini_is_dir(file))
		ft_printf_fd(STDERR_FILENO, "minishell: %s: Is a directory\n", file);
	else if (fd < 0 && access(file, R_OK))
		ft_printf_fd(STDERR_FILENO, "minishell: %s: Permission denied\n", file);
	redir_node->input_fd = fd;
}
