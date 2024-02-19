/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:37:35 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/19 23:33:53 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int heredocendedwith_c(int state, int flag)
{
	static int	ret;

	if(flag == 1)
		ret = state;
	return (ret);
}

void	signal_handler_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		heredocendedwith_c(1, 1);
		exitstatus(-1, 1);
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
	}
}

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		exitstatus(1, 1);
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}