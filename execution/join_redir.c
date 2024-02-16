/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 17:00:00 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/16 21:26:22 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	new_cmd_node(int *flag, t_cmd **cmd, char *buffer, t_cmd *save)
{
	t_cmd	*new;
	t_cmd	*curr;

	curr = *cmd;
	new = rad_malloc(sizeof(t_cmd), 0, COMMAND);
	if (!new)
		return ;
	new->cmd = buffer;
	new->next = NULL;
	new->heredocfd = save->heredocfd;
	new->expand = save->expand;
	new->spaceafter = save->spaceafter;
	if (*flag == 1)
	{
		*flag = 0;
		*cmd = new;
	}
	else
	{
		while (curr->next)
			curr = curr->next;
		curr ->next = new;
	}
}

void	new_cmdpart1(t_cmd **curr, int *flag, t_cmd **new, t_env *env)
{
	t_cmd	*save;
	char	*buffer;

	buffer = NULL;
	save = *curr;
	buffer = ft_strdup((*curr)->cmd);
	new_cmd_node(flag, new, buffer, save);
	buffer = NULL;
	(*curr) = (*curr)->next;
	save = *curr;
	(*curr)->spaceafter = 0;
	while (*curr && (*curr)->spaceafter != 1
		&& (*curr)->cmd[0] != '>' && (*curr)->cmd[0] != '<')
	{
		buffer = ft_strjoin(buffer, argextraction(*curr, env));
		if(buffer == NULL)
			buffer = ft_strdup("");
		*curr = (*curr)->next;
	}
	new_cmd_node(flag, new, buffer, save);
}

t_cmd	*new_cmd_list(t_cmd *root, t_env *env)
{
	t_cmd	*new;
	t_cmd	*curr;
	char	*buffer;
	t_cmd	*save;
	int		flag;

	flag = 1;
	buffer = NULL;
	curr = root;
	while (curr)
	{
		if (curr->cmd && (curr->cmd[0] == '<' || curr->cmd[0] == '>'))
		{
			if(array_len(var_toarray(curr->next->cmd, env)) > 1)
			{
				wrerror("turboshell: ");
				wrerror(curr->next->cmd);
				wrerror(": ambiguous redirection\n");
			}
			new_cmdpart1(&curr, &flag, &new, env);
		}
		else
		{
			save = curr;
			
			buffer = ft_strdup(curr->cmd);
			new_cmd_node(&flag, &new, buffer, save);
			curr = curr->next;
		}
		if (!curr)
			break ;
		buffer = NULL;
	}
	return (new);
}
