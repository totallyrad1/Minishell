/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 17:04:36 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/22 08:03:59 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	throwerror_forin(t_cmd *curr, int infile)
{
	if (curr->next && ft_strchr(curr->next->cmd, '*')
		&& (array_len(wildcard(curr->next)) != 1))
	{
		wrerror("turboshell: ");
		wrerror(curr->next->cmd);
		wrerror(": ambiguous redirection\n");
	}
	else if (infile == -1 && curr->next->ambiguous != 1 && (curr->cmd
			&& curr->cmd[0] == '<' && curr->cmd[1] == '\0'))
	{
		wrerror("turboshell: ");
		wrerror(curr->next->cmd);
		wrerror(": No such file or directory\n");
	}
}

static void	get_infile(t_cmd *curr, t_env *env, int *infile)
{
	if (curr->cmd && curr->word != 1
		&& curr->cmd[0] == '<' && curr->cmd[1] == '<')
	{
		if (curr->expandheredoc == 0)
			*infile = heredoc_expanded(curr->heredocfd, env);
		else
		{
			if (*infile > 2)
				close(*infile);
			*infile = curr->heredocfd;
		}
		addfd(*infile, 1);
	}
	else if (curr->cmd && curr->word != 1
		&& curr->cmd[0] == '<' && curr->cmd[1] == '\0')
	{
		if (checkreadpermissions(curr->next->cmd, infile) == 0)
			return ;
		if (*infile > 2)
			close(*infile);
		*infile = open(curr->next->cmd, O_RDONLY);
		addfd(*infile, 1);
		throwerror_forin(curr, *infile);
	}
}

static void	throwerrorfor_out(t_cmd *curr)
{
	if (curr->next && ft_strchr(curr->next->cmd, '*')
		&& array_len(wildcard(curr->next)))
	{
		wrerror("turboshell: ");
		wrerror(curr->next->cmd);
		wrerror(": ambiguous redirection\n");
	}
}

int	openoutfi(int *outfi, t_cmd *curr)
{
	if (checkwritepermissions(curr->next->cmd, outfi) == 0)
		return (0);
	closeoutfile(*outfi);
	*outfi = open(curr->next->cmd, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	throwerrorfor_out(curr);
	addfd(*outfi, 1);
	return (1);
}

void	getfds(t_cmd *curr, t_env *env, int *infile, int *outfi)
{
	while (curr && *infile != -1 && *outfi != -1 && curr->ambiguous != 1)
	{
		if (curr->cmd && curr->word != 1 && curr->cmd[0] == '<')
			get_infile(curr, env, infile);
		else if (curr->cmd && curr->word != 1
			&& curr->cmd[0] == '>' && curr->cmd[1] == '>')
		{
			if (checkwritepermissions(curr->next->cmd, outfi) == 0)
				break ;
			closeoutfile(*outfi);
			*outfi = open(curr->next->cmd, O_CREAT | O_WRONLY | O_APPEND, 0644);
			throwerrorfor_out(curr);
			addfd(*outfi, 1);
		}
		else if (curr->cmd && curr->word != 1
			&& curr->cmd[0] == '>' && curr->cmd[1] == '\0')
		{
			if (!openoutfi(outfi, curr))
				break ;
		}
		curr = curr->next;
	}
}
