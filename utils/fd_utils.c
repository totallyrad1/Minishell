/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 17:04:36 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/19 14:38:23 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int checkreadpermissions(char *str, int *infile)
{
	if (access(str, F_OK) == 0 && access(str, R_OK) != 0)
	{
		wrerror("bash: ");
		wrerror(str);
		wrerror(": Permission denied\n");
		*infile = -1;
		return (0);
	}
	return (1);
}

int checkwritepermissions(char *str, int *outfile)
{
	if (access(str, F_OK) == 0 && access(str, W_OK) != 0)
	{
		wrerror("bash: ");
		wrerror(str);
		wrerror(": Permission denied\n");
		*outfile = -1;
		return (0);
	}
	return (1);
}

void get_infile(t_cmd *curr, t_env *env, int *infile)
{
	if(curr->cmd && curr->word != 1 && curr->cmd[0] == '<' && curr->cmd[1] == '<')
	{
		if(curr->expandheredoc == 0)
			*infile = heredoc_expanded(curr->heredocfd, env);
		else
			*infile = curr->heredocfd;
	}
	else if(curr->cmd && curr->word != 1 && curr->cmd[0] == '<' && curr->cmd[1] == '\0')
	{
		if(checkreadpermissions(curr->next->cmd, infile) == 0)
			return ;
		*infile = open(curr->next->cmd , O_RDONLY);
		if (curr->next && ft_strchr(curr->next->cmd, '*') && array_len(wildcard(curr->next, NULL)))
		{
			wrerror("turboshell: ");
			wrerror(curr->next->cmd);
			wrerror(": ambiguous redirection\n");	
		}
		else if(*infile == -1 && curr->next->ambiguous != 1 && (curr->cmd && curr->cmd[0] == '<' && curr->cmd[1] == '\0'))
		{
			wrerror("turboshell: ");
			wrerror(curr->next->cmd);
			wrerror(": No such file or directory\n");
		}
	}
}

void getfds(t_cmd *cmd, t_env *env, int *infile, int *outfile)
{
	t_cmd	*curr;

	curr = cmd;
	while(curr && *infile != -1 && *outfile != -1 && curr->ambiguous != 1)
	{
		if(curr->cmd && curr->word != 1 && curr->cmd[0] == '<')
			get_infile(curr, env, infile);
		else if (curr->cmd && curr->word != 1 && curr->cmd[0] == '>' && curr->cmd[1] == '>')
		{
			if(checkwritepermissions(curr->next->cmd, outfile) == 0)
				break;
			*outfile = open(curr->next->cmd , O_CREAT | O_WRONLY | O_APPEND, 0644);
		}
		else if(curr->cmd && curr->word != 1 && curr->cmd[0] == '>' && curr->cmd[1] == '\0')
		{
			if(checkwritepermissions(curr->next->cmd, outfile) == 0)
				break;
			*outfile = open(curr->next->cmd , O_CREAT | O_WRONLY | O_TRUNC, 0644);
		}
		if(*outfile == -1 || *infile == -1)
			break;
		curr = curr->next;
	}
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
