/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 17:00:00 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/19 20:50:54 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	new_cmd_node(t_cmd **cmd, t_ncmdlst **vars)
{
	t_cmd	*new;
	t_cmd	*curr;

	curr = *cmd;
	new = rad_malloc(sizeof(t_cmd), 0, COMMAND);
	if (!new)
		return (ft_exit(NULL));
	new->cmd = (*vars)->buffer;
	new->next = NULL;
	new->heredocfd = (*vars)->save->heredocfd;
	new->expandheredoc = (*vars)->save->expandheredoc;
	new->spaceafter = (*vars)->save->spaceafter;
	new->ambiguous = (*vars)->ambiguous;
	new->word = (*vars)->word;
	if ((*vars)->flag == 1)
	{
		(*vars)->flag = 0;
		*cmd = new;
	}
	else
	{
		while (curr->next)
			curr = curr->next;
		curr ->next = new;
	}
}

void	new_cmdpart1_1(t_ncmdlst **vars, t_cmd **curr, t_env *env)
{
	if ((*vars)->save1->cmd[1] != '<'
		&& (*curr)->cmd[0] == '$' && (*curr)->cmd[1]
		&& (array_len(var_toarray((*curr)->cmd, env)) > 1
			|| array_len(var_toarray((*curr)->cmd, env)) == 0))
	{
		wrerror("turboshell: ");
		wrerror((*curr)->cmd);
		wrerror(": ambiguous redirection\n");
		(*vars)->ambiguous = 1;
		(*vars)->buffer = NULL;
	}
	else
	{
		(*vars)->buffer = ft_strjoin((*vars)->buffer,
				argextraction(*curr, env));
	}
	if ((*vars)->buffer == NULL)
		(*vars)->buffer = ft_strdup("");
	*curr = (*curr)->next;
}

void	new_cmdpart1(t_cmd **curr, t_ncmdlst **vars, t_cmd **new, t_env *env)
{
	(*vars)->buffer = NULL;
	(*vars)->save = *curr;
	(*vars)->save1 = *curr;
	(*vars)->word = 0;
	(*vars)->buffer = ft_strdup((*curr)->cmd);
	new_cmd_node(new, vars);
	(*vars)->buffer = NULL;
	(*curr) = (*curr)->next;
	(*vars)->save = *curr;
	(*vars)->word = 1;
	(*curr)->spaceafter = 0;
	(*vars)->ambiguous = 0;
	while (*curr && (*curr)->spaceafter != 1
		&& (*curr)->cmd[0] != '>' && (*curr)->cmd[0] != '<')
		new_cmdpart1_1(vars, curr, env);
	new_cmd_node(new, vars);
}

void	set_word(t_ncmdlst **vars, t_cmd *curr)
{
	if ((curr->cmd[0] == '<' && curr->cmd[1] == '<'))
		(*vars)->word = 0;
	else
		(*vars)->word = 1;
}

t_cmd	*new_cmd_list(t_cmd *curr, t_env *env)
{
	t_ncmdlst	*vars;
	t_cmd		*new;

	vars = rad_malloc(sizeof(t_ncmdlst), 0, COMMAND);
	if (!vars)
		ft_exit(NULL);
	vars->flag = 1;
	vars->buffer = NULL;
	while (curr)
	{
		if (curr->cmd && ((curr->cmd[0] == '<'
					&& !curr->cmd[1]) || curr->cmd[0] == '>'))
			new_cmdpart1(&curr, &vars, &new, env);
		else
		{
			vars->save = curr;
			set_word(&vars, curr);
			vars->buffer = ft_strdup(curr->cmd);
			new_cmd_node(&new, &vars);
			curr = curr->next;
		}
		vars->buffer = NULL;
	}
	return (new);
}
