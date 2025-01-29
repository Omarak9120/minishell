/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_utils_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:24:10 by oabdelka          #+#    #+#             */
/*   Updated: 2025/01/29 18:34:59 by oabdelka         ###   ########.fr       */
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
/*
#include "../include/minishell.h"
#include <sys/stat.h>
#include <errno.h>

int    mini_is_dir(char *file)
{
    struct stat st;
    return (stat(file, &st) == 0 && S_ISDIR(st.st_mode));
}

static void mini_redir_error(t_mini *mini, char *file, int err_type)
{
    mini->status = 1;
    if (err_type == E_NOENT)
        ft_printf_fd(2, "minishell: %s: No such file or directory\n", file);
    else if (err_type == E_ISDIR)
        ft_printf_fd(2, "minishell: %s: Is a directory\n", file);
    else if (err_type == E_PERM)
        ft_printf_fd(2, "minishell: %s: Permission denied\n", file);
    else if (err_type == E_INTR)
        ft_printf_fd(2, "minishell: interrupted\n");
    
    if (err_type == E_ISDIR || err_type == E_PERM) mini->status = 126;
    if (err_type == E_NOENT) mini->status = 127;
    if (err_type == E_INTR) mini->status = 130;
}

void    mini_handle_out_redir(t_mini *mini, t_cmd *redir_node, char *file)
{
    int fd;

    if (redir_node->output_fd > 2)
        close(redir_node->output_fd);
    fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        if (errno == EINTR)
            mini_redir_error(mini, file, E_INTR);
        else if (access(file, F_OK) == -1)
            mini_redir_error(mini, file, E_NOENT);
        else if (mini_is_dir(file))
            mini_redir_error(mini, file, E_ISDIR);
        else
            mini_redir_error(mini, file, E_PERM);
        fd = -1;
    }
    redir_node->output_fd = fd;
}

void    mini_handle_in_redir(t_mini *mini, t_cmd *redir_node, char *file)
{
    int fd;

    if (redir_node->input_fd > 2)
        close(redir_node->input_fd);
    fd = open(file, O_RDONLY);
    if (fd < 0) {
        if (errno == EINTR)
            mini_redir_error(mini, file, E_INTR);
        else if (access(file, F_OK) == -1)
            mini_redir_error(mini, file, E_NOENT);
        else if (mini_is_dir(file))
            mini_redir_error(mini, file, E_ISDIR);
        else
            mini_redir_error(mini, file, E_PERM);
        fd = -1;
    }
    redir_node->input_fd = fd;
}

void    mini_handle_append_redir(t_mini *mini, t_cmd *redir_node, char *file)
{
    int fd;

    if (redir_node->output_fd > 2)
        close(redir_node->output_fd);
    fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd < 0) {
        if (errno == EINTR)
            mini_redir_error(mini, file, E_INTR);
        else if (access(file, F_OK) == -1)
            mini_redir_error(mini, file, E_NOENT);
        else if (mini_is_dir(file))
            mini_redir_error(mini, file, E_ISDIR);
        else
            mini_redir_error(mini, file, E_PERM);
        fd = -1;
    }
    redir_node->output_fd = fd;
}

void    mini_handle_heredoc_redir(t_mini *mini, t_cmd *redir_node, char *file)
{
    int fd;

    if (redir_node->input_fd > 2)
        close(redir_node->input_fd);
    fd = open(file, O_RDONLY);
    if (fd < 0) {
        if (errno == EINTR)
            mini_redir_error(mini, file, E_INTR);
        else if (access(file, F_OK) == -1)
            mini_redir_error(mini, file, E_NOENT);
        else if (mini_is_dir(file))
            mini_redir_error(mini, file, E_ISDIR);
        else
            mini_redir_error(mini, file, E_PERM);
        fd = -1;
    }
    redir_node->input_fd = fd;
}*/