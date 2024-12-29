#include "../../includes/minishell.h"

// char	*getinfo(t_data *data)
// {
// 	char	*info;
// 	char	*sig;
// 	char	*pwd;

// 	pwd = get_env(data->env_list, "PWD");
// 	sig = ft_itoa(data->cmd.status);
// 	info = ft_strdup("");
// 	info = ft_strjoingnl(info, BLUE_BRIGHT);
// 	info = ft_strjoingnl(info, pwd);
// 	info = ft_strjoingnl(info, RESET);
// 	info = ft_strjoingnl(info, BG_RED_BRIGHT);
// 	info = ft_strjoingnl(info, sig);
// 	info = ft_strjoingnl(info, RESET);
// 	info = ft_strjoingnl(info, GREEN "⫤ " RESET);
// 	if (sig)
// 		free(sig);
// 	if (pwd != NULL)
// 		free(pwd);
// 	return (info);
// }

char	*getinfo(t_data *data)
{
	char	*info;
	char	*sig;
	char	*pwd;

	pwd = get_env(data->env_list, "PWD");
	sig = ft_itoa(data->cmd.status);

	info = ft_strdup("");
	if (!info)
		return (NULL);
	/*
	 * Example prompt design:
	 *  [ /current/path : 0 ] ⫤ 
	 *    - "/current/path" in BLUE_BRIGHT
	 *    - Status in BG_RED_BRIGHT
	 *    - Then the green arrow
	 */
	info = ft_strjoingnl(info, BLUE_BRIGHT "[ " RESET);
	info = ft_strjoingnl(info, (pwd ? pwd : "unknown_dir"));
	info = ft_strjoingnl(info, BLUE_BRIGHT " : " RESET);
	info = ft_strjoingnl(info, BG_RED_BRIGHT);
	info = ft_strjoingnl(info, sig);
	info = ft_strjoingnl(info, RESET);
	info = ft_strjoingnl(info, BLUE_BRIGHT " ]" RESET " ");
	info = ft_strjoingnl(info, GREEN ">> " RESET);

	free(sig);
	free(pwd);
	return (info);
}

void	interactivemode(t_data *data, char **input)
{
	char	*info;

	signal(SIGINT, interactivehandle_sigint);
	signal(SIGQUIT, interactivehandle_sigquit);
	signal(SIGTSTP, SIG_IGN);
	while (1)
	{
		info = getinfo(data);
		*input = readline(info);
		free(info);
		if (input != NULL)
			break ;
		if (ft_strlen(*input) != 0)
		{
			break ;
		}
	}
	if (g_signalint != 0)
	{
		data->cmd.status = g_signalint;
		g_signalint = 0;
	}
	(void)data;
}

void	noninteractivemode(t_data *data, char **input)
{
	signal(SIGINT, noninteractivehandle_sigint);
	signal(SIGQUIT, noninteractivehandle_sigint);
	signal(SIGTSTP, SIG_IGN);
	while (data->cmd.running == 1 && g_signalint != 130)
	{
		if (g_signalint == 130)
		{
			handlesignal(data);
			printf("\n");
			data->cmd.status = g_signalint;
			g_signalint = 0;
			break ;
		}
	}
	(void)*input;
}
