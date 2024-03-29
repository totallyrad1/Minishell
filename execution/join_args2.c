/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_args2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 11:26:05 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/22 17:59:56 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	skip_redirections(t_cmd **temp)
{
	if (*temp && (*temp)->word != 1 && (*temp)->cmd
		&& ((*temp)->cmd[0] == '>' || (*temp)->cmd[0] == '<'))
	{
		while (*temp && (*temp)->cmd
			&& ((*temp)->cmd[0] == '>' || (*temp)->cmd[0] == '<'))
		{
			(*temp) = (*temp)->next;
			if (*temp)
				(*temp) = (*temp)->next;
		}
	}
}

void	make_args_node(t_cmd **args, t_margs **vars, t_cmd **cmd)
{
	t_cmd	*new;
	t_cmd	*curr;

	new = rad_malloc(sizeof(t_cmd), 0, COMMAND);
	setvars_argsnode(vars, &new, cmd);
	if ((*vars)->flag == 1)
	{
		*args = new;
		(*vars)->flag = 0;
	}
	else
	{
		curr = *args;
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
}

void	makearpart1(t_cmd **cmd, t_cmd **new_lst, t_margs **vars, t_env *env)
{
	(*vars)->buffer = argextraction(*cmd, env);
	if ((*cmd)->cmd[0] == '\'' || (*cmd)->cmd[0] == '\"')
		(*vars)->expand = 0;
	else
		(*vars)->expand = 1;
	(*vars)->heredocfd = (*cmd)->heredocfd;
	(*vars)->heredocexpand = (*cmd)->expandheredoc;
	(*vars)->ambiguos = (*cmd)->ambiguous;
	(*vars)->word = (*cmd)->word;
	(*vars)->spaceafter = (*cmd)->spaceafter;
	make_args_node(new_lst, vars, cmd);
	(*cmd) = (*cmd)->next;
	(*vars)->buffer = ft_strdup((*cmd)->cmd);
	if ((*cmd)->cmd[0] == '\'' || (*cmd)->cmd[0] == '\"')
		(*vars)->expand = 0;
	else
		(*vars)->expand = 1;
	(*vars)->heredocfd = (*cmd)->heredocfd;
	(*vars)->heredocexpand = (*cmd)->expandheredoc;
	(*vars)->ambiguos = (*cmd)->ambiguous;
	(*vars)->word = (*cmd)->word;
	(*vars)->spaceafter = (*cmd)->spaceafter;
	make_args_node(new_lst, vars, cmd);
	*cmd = (*cmd)->next;
}

void	makea_part2_2(t_cmd **cmd, t_cmd **new_lst, t_margs **vars, t_env *env)
{
	(*vars)->buffer = argextraction(*cmd, env);
	if ((*vars)->buffer && !(*vars)->buffer[0])
		(*vars)->buffer = NULL;
	(*vars)->heredocfd = (*cmd)->heredocfd;
	(*vars)->heredocexpand = (*cmd)->expandheredoc;
	(*vars)->ambiguos = (*cmd)->ambiguous;
	(*vars)->word = (*cmd)->word;
	(*vars)->spaceafter = (*cmd)->spaceafter;
	if ((*cmd)->cmd[0] == '\'' || (*cmd)->cmd[0] == '\"')
		(*vars)->expand = 0;
	else
		(*vars)->expand = 1;
	make_args_node(new_lst, vars, cmd);
}
