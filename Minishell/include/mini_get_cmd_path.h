/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_get_cmd_path.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:54:32 by oabdelka          #+#    #+#             */
/*   Updated: 2025/02/01 19:54:35 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_GET_CMD_PATH_H
# define MINI_GET_CMD_PATH_H

typedef struct s_get_cmd_path
{
	char	*cmd_name;
	char	*path;
	char	*part_path;
	char	**splited_path;
	int		i;
}	t_get_cmd_path;

#endif
