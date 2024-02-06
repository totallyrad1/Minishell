/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 19:59:53 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/06 17:23:04 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_dollarsign(t_token **cmd, t_vars *vars)
{
	vars->tmp = vars->i;
	if(vars->cmd[vars->i] == '$')
		vars->i++;
	while(vars->cmd[vars->i] && (ft_alphanum(vars->cmd[vars->i]) == 1 || vars->cmd[vars->i] == '?'))
		vars->i++;
	if (vars->flag == 1)
	{
		(*cmd)->cmd = ft_substr(vars->cmd, vars->tmp, vars->i - vars->tmp);
		(*cmd)->state = GENERAL;
		(*cmd)->spaceafter = hasspaceafter(vars->cmd, vars->i);
		vars->flag = 0;
	}
	else
		ft_newnode(cmd, ft_substr(vars->cmd, vars->tmp, vars->i - vars->tmp), GENERAL, hasspaceafter(vars->cmd, vars->i));
	return (ft_switch(cmd, vars));
}

int	ft_switch(t_token **cmd, t_vars *vars)
{
	if (vars->cmd[vars->i])
	{
		if (ft_isspace(vars->cmd[vars->i]) == 1)
			return (ft_space(cmd, vars));
		else if (ft_isquote(vars->cmd[vars->i]) == 1)
			return (ft_quote(cmd, vars));
		else if(vars->cmd[vars->i] == '$')
			return ft_dollarsign(cmd, vars);
		else if (islimiter(vars->cmd[vars->i]) == 1)
			return (ft_separator(cmd, vars));
		else if (vars->cmd[vars->i] == '(' || vars->cmd[vars->i] == ')')
			return (ft_bracket(cmd, vars));
		else
			return (ft_char(cmd, vars));
	}
	return (0);
}

void	give_state_and_type(t_token **cmd)
{
	t_token	*curr;
	
	curr = *cmd;
	while (curr)
	{
		if(curr->cmd)
			curr->type = getlimitertoken(curr->cmd[0], curr->cmd[1]);
		// if (curr->cmd[0] == '"')
		// 	curr->state = IN_DQUOTE;
		// else if (curr->cmd[0] == '\'')
		// 	curr->state = IN_QUOTE;
		// else
		// 	curr->state = GENERAL;
		curr = curr->next;
	}
}
