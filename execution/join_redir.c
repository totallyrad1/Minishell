/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 17:00:00 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/17 22:55:41 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	new_cmd_node(int *flag, t_cmd **cmd, char *buffer, t_cmd *save, int ambiguos)
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
	new->expandheredoc = save->expandheredoc;
	new->spaceafter = save->spaceafter;
	new->ambiguous = ambiguos;
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
	t_cmd	*save1;
	char	*buffer;
	int		ambiguous;

	buffer = NULL;
	save = *curr;
	save1 = *curr;
	buffer = ft_strdup((*curr)->cmd);
	new_cmd_node(flag, new, buffer, save, 0);
	buffer = NULL;
	(*curr) = (*curr)->next;
	printf("%s\n", save->cmd);
	save = *curr;
	(*curr)->spaceafter = 0;
	ambiguous = 0;
	while (*curr && (*curr)->spaceafter != 1
		&& (*curr)->cmd[0] != '>' && (*curr)->cmd[0] != '<')
	{
		if(save1->cmd[1] != '<' && (*curr)->cmd[0] == '$' &&  (*curr)->cmd[1] && (array_len(var_toarray((*curr)->cmd, env)) > 1 || array_len(var_toarray((*curr)->cmd, env)) == 0))
		{
			wrerror("turboshell: ");
			wrerror((*curr)->cmd);
			wrerror(": ambiguous redirection1\n");
			ambiguous = 1;
			buffer = NULL;
		}
		else {
			buffer = ft_strjoin(buffer, argextraction(*curr, env));
		}
		if(buffer == NULL)
			buffer = ft_strdup("");
		*curr = (*curr)->next;
	}
	new_cmd_node(flag, new, buffer, save, ambiguous);
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
		if (curr->cmd && ((curr->cmd[0] == '<' && !curr->cmd[1]) || curr->cmd[0] == '>'))
			new_cmdpart1(&curr, &flag, &new, env);
		else
		{
			save = curr;
			buffer = ft_strdup(curr->cmd);
			new_cmd_node(&flag, &new, buffer, save, 0);
			curr = curr->next;
		}
		if (!curr)
			break ;
		buffer = NULL;
	}
	return (new);
}
