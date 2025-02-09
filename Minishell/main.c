/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:53:44 by oabdelka          #+#    #+#             */
/*   Updated: 2025/02/03 16:44:23 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

static void	no_error_detect(t_mini *mini);
static void	recursive_init(t_mini *mini);

int	main(void)
{
	t_mini	*mini;

	mini = get_address();
	ctrl_signal(mini);
	mini_getenv(mini);
	update_shlvl(mini);
	mini->status = 0;
	while (42)
	{
		recursive_init(mini);
		if (mini->cmd_line == NULL)
		{
			ctrl_d_exit();
			break ;
		}
		if (mini->cmd_line[0] == '\0')
			continue ;
		add_history(mini->cmd_line);
		tokenizer(mini);
		if (!mini->syntax_error && mini->token_list)
			no_error_detect(mini);
	}
	ft_free_trashman(ft_get_mem_address());
	ft_free_trashman_env(ft_get_mem_address_env());
}

void	no_error_detect(t_mini *mini)
{
	parser(mini);
	expansion(mini);
	redirect(mini);
	execute(mini);
}

void	recursive_init(t_mini *mini)
{
	mini_init(mini);
	mini->int_action.sa_handler = sig_handler;
	sigaction(SIGINT, &mini->int_action, NULL);
	mini->quit_action.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &mini->quit_action, NULL);
	mini->cmd_line = readline("prompt > ");
	ft_collect_mem(mini->cmd_line);
}
