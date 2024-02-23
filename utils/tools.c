/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:17:14 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/23 00:40:55 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_newnode(t_token **cmd, char *value, int spaceafter)
{
	t_token	*new_node;
	t_token	*curr;

	new_node = rad_malloc(sizeof(t_token), 0, COMMAND);
	curr = *cmd;
	new_node->visited = 0;
	new_node->spaceafter = spaceafter;
	new_node->next = NULL;
	new_node->cmd = value;
	while (curr->next)
		curr = curr->next;
	curr->next = new_node;
	new_node->prev = curr;
}

t_token	*init_token(void)
{
	t_token	*cmd;

	cmd = rad_malloc(sizeof(t_token), 0, COMMAND);
	cmd->visited = 0;
	cmd->spaceafter = 0;
	cmd->next = NULL;
	cmd->cmd = NULL;
	cmd->prev = NULL;
	return (cmd);
}

void	wrerror(char *str)
{
	if (str)
		write(2, str, ft_strlen(str));
}

void	reset_terminal(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
	{
		perror("tcgetattr");
		ft_exit(NULL);
	}
	term.c_iflag = ICRNL;
	term.c_oflag = OPOST | ONLCR;
	// term.c_cflag = CS8 | CREAD;
	term.c_lflag = ISIG | ICANON | ECHO | ECHOE | ECHOK | ECHOCTL | ECHOKE;
	// term.c_cc[VMIN] = 1;
	// term.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &term) == -1)
	{
		perror("tcsetattr");
		ft_exit(NULL);
	}
}
