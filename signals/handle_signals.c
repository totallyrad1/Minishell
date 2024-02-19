/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:37:35 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/19 01:47:43 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	signal_handler_heredoc(int signum, int *ptr)
{
	static int	*flag;

	if (signum == -22)
		flag = ptr;
	if (signum == SIGINT)
	{
		exitstatus(1, 1);
		*flag = 1;
		printf("\n");
	}
}

void	signal_handler(int signum)
{
	if (waitpid(-1, NULL, WNOHANG) == 0)
		return ;
	if (signum == SIGINT)
	{
		exitstatus(1, 1);
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}