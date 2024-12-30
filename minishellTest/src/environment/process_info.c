/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjamil <mjamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 20:15:12 by mjamil            #+#    #+#             */
/*   Updated: 2024/12/30 20:15:12 by mjamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//fetch_pid_info
char    *read_pid_line(int fd)
{
    static char   temp_buffer[256];
    ssize_t       read_bytes;

    read_bytes = read(fd, temp_buffer, sizeof(temp_buffer) - 1);
    if (read_bytes <= 0)
        return (NULL);
    temp_buffer[read_bytes] = '\0';
    return (strstr(temp_buffer, "Pid:"));
}

//open_status_file
ssize_t    read_status_file(char *output_buffer, size_t max_size)
{
    int         file_descriptor;
    ssize_t     read_bytes;

    file_descriptor = open("/proc/self/status", O_RDONLY);
    read_bytes = -1;
    if (file_descriptor != -1)
    {
        read_bytes = read(file_descriptor, output_buffer, max_size - 1);
        close(file_descriptor);
    }
    return (read_bytes);
}

//split_env_var
void    ft_split_env(char *env_var, char **var_key, char **var_value)
{
    char    *equal_pos;

    equal_pos = ft_strchr(env_var, '=');
    if (equal_pos)
    {
        *var_key = ft_strndup(env_var, equal_pos - env_var);
        *var_value = ft_strdup(equal_pos + 1);
    }
    else
    {
        *var_key = ft_strdup(env_var);
        *var_value = NULL;
    }
}

//get_process_uid
pid_t    ft_getuid(void)
{
    char        temp_buffer[256];
    ssize_t     bytes_read;
    char        *uid_line;
    pid_t       user_id;

    user_id = -1;
    bytes_read = open_status_file(temp_buffer, sizeof(temp_buffer));
    if (bytes_read > 0)
    {
        temp_buffer[bytes_read] = '\0';
        uid_line = ft_strstr(temp_buffer, "Uid:");
        if (uid_line)
        {
            uid_line = ft_strchr(uid_line, '\t');
            if (uid_line)
                user_id = ft_atoi(uid_line + 1);
        }
    }
    return (user_id);
}
