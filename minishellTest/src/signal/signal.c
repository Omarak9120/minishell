#include "../../includes/minishell.h"



char	*getinfo(t_data *data)
{
	char	*info;
	(void)data;
	// char	*sig;
	// char	*pwd;

	// pwd = get_env(data->env_list, "PWD");
	// sig = ft_itoa(data->cmd.status);

	// Start with an empty string
	info = ft_strdup(GREEN_BRIGHT ">>" RESET);
	if (!info)
		return (NULL);

	// Example palette:
	//   [ /path : 0 ] ⫤ 
	//  - Brackets in CYAN
	//  - Status in bold YELLOW
	//  - Final arrow in GREEN
	
	// info = ft_strjoingnl(info, CYAN "[ " RESET);
	// info = ft_strjoingnl(info, RED_BRIGHT);
	// info = ft_strjoingnl(info, (pwd ? pwd : "(no PWD)"));
	// info = ft_strjoingnl(info, CYAN " : " RESET);
	// info = ft_strjoingnl(info, YELLOW_BRIGHT);
	// info = ft_strjoingnl(info, sig);
	// info = ft_strjoingnl(info, RESET);
	// info = ft_strjoingnl(info, CYAN " ] " RESET);
	// info = ft_strjoingnl(info, GREEN ">> " RESET);
	// free(sig);
	// free(pwd);
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
