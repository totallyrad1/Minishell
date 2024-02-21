/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_args3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 23:50:15 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/21 18:36:55 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	make_args_part3(t_cmd **cmd, t_cmd **new, t_margs **vars, t_env *env)
{
	(*vars)->buffer = argextraction(*cmd, env);
	(*vars)->expand = 1;
	(*vars)->heredocfd = (*cmd)->heredocfd;
	(*vars)->heredocexpand = (*cmd)->expandheredoc;
	(*vars)->ambiguos = (*cmd)->ambiguous;
	(*vars)->spaceafter = (*cmd)->spaceafter;
	(*vars)->word = (*cmd)->word;
	if ((*cmd)->cmd[0] == '\'' || (*cmd)->cmd[0] == '\"')
		(*vars)->expand = 0;
	else
		(*vars)->expand = 1;
	make_args_node(new, vars);
	*cmd = (*cmd)->next;
}

void	set_varsforpart2_1(t_cmd **cmd, t_margs **vars, char *tmp)
{
	(*vars)->buffer = ft_strdup(tmp);
	(*vars)->expand = 1;
	(*vars)->heredocfd = (*cmd)->heredocfd;
	(*vars)->heredocexpand = (*cmd)->expandheredoc;
	(*vars)->ambiguos = (*cmd)->ambiguous;
	(*vars)->word = (*cmd)->word;
}

void	set_spaceafter(t_margs **vars, t_cmd **cmd, t_env *env)
{
	if (check_expanded_var((*cmd)->cmd, env) == 1 || (*cmd)->spaceafter == 1)
		(*vars)->spaceafter = 1;
	else
		(*vars)->spaceafter = 0;
}

void	make_args_part2_1(t_cmd **cmd, t_cmd **new, t_margs **vars, t_env *env)
{
	int		j;
	char	**tmp;

	j = -1;
	tmp = var_toarray((*cmd)->cmd, env);
	if (tmp)
	{
		while (tmp[++j])
		{
			set_varsforpart2_1(cmd, vars, tmp[j]);
			if (j == 0)
			{
				set_spaceafter(vars, cmd, env);
				make_args_node(new, vars);
			}
			else
			{
				(*vars)->spaceafter = 1;
				make_args_node(new, vars);
			}
			(*vars)->buffer = NULL;
		}
	}
	else
		makea_part2_2(cmd, new, vars, env);
}

t_cmd	*make_args_lst(t_cmd *cmd, t_env *env)
{
	t_margs	*vars;
	t_cmd	*new;

	vars = rad_malloc(sizeof(t_margs), 0, COMMAND);
	vars->flag = 1;
	vars->buffer = NULL;
	while (cmd)
	{
		vars->buffer = NULL;
		if (cmd->cmd && (cmd->cmd[0] == '<' || cmd->cmd[0] == '>'))
			makearpart1(&cmd, &new, &vars, env);
		else if (cmd->cmd && cmd->cmd[0] == '$' && cmd->cmd[1])
		{
			make_args_part2_1(&cmd, &new, &vars, env);
			cmd = cmd->next;
		}
		else if (cmd->cmd)
			make_args_part3(&cmd, &new, &vars, env);
	}
	return (new);
}
