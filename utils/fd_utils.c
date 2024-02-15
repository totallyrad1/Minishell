/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 17:04:36 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/15 17:59:56 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int getlastinfile(t_cmd *cmd, t_env *env)
{
	int		fd;
	t_cmd	*curr;

	curr = cmd;
	fd = 0;
	while(curr && fd != -1)
	{
		if(curr->cmd[0] == '<' && curr->cmd[1] == '<')
		{
			if(curr->expand == 0)
				fd = heredoc_expanded(curr->heredocfd, env);
			else
				fd = curr->heredocfd;
		}
		else if(curr->cmd[0] == '<' && curr->cmd[1] == '\0')
			fd = open(curr->next->cmd , O_RDONLY);
		if(fd == -1 && (curr->cmd[0] == '<' && curr->cmd[1] == '\0'))
		{
			wrerror("turboshell: ");
			wrerror(curr->next->cmd);
			wrerror(": No such file or directory\n");
		}
		curr = curr->next;
	}
	return fd;
}

int getlastoutfile(t_cmd *cmd)
{
	int		fd;
	t_cmd	*curr;

	fd = 1;
	curr = cmd;
	while (curr)
	{
		if (curr->cmd[0] == '>' && curr->cmd[1] == '>')
		{
			fd = open(curr->next->cmd , O_CREAT | O_WRONLY | O_APPEND, 0644);
		}
		else if(curr->cmd[0] == '>' && curr->cmd[1] == '\0')
		{
			fd = open(curr->next->cmd , O_CREAT | O_WRONLY | O_TRUNC, 0644);
		}
		curr = curr->next;
	}
	return fd;
}

void changeinfile(int fd)
{
	if (fd != 0)
	{
		dup2(fd,STDIN_FILENO);
		close(fd);
	}
}

void changeoutfile(int fd)
{
	if (fd != 1)
	{
		dup2(fd,STDOUT_FILENO);
		close(fd);
	}
}
