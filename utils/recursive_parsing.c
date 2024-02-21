/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:05:06 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/21 16:32:34 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_char(t_token **cmd, t_vars *vars)
{
	vars->tmp = vars->i;
	while (vars->cmd[vars->i] && islimiter(vars->cmd[vars->i]) == 0
		&& ft_isquote(vars->cmd[vars->i]) == 0
		&& ft_isspace(vars->cmd[vars->i]) == 0
		&& (vars->cmd[vars->i] != ')' && vars->cmd[vars->i] != '('))
		vars->i++;
	if (vars->flag == 1)
	{
		(*cmd)->cmd = ft_substr(vars->cmd, vars->tmp, vars->i - vars->tmp);
		(*cmd)->spaceafter = hasspaceafter(vars->cmd, vars->tmp - 1);
		vars->flag = 0;
	}
	else
		ft_newnode(cmd, ft_substr(vars->cmd,
				vars->tmp, vars->i - vars->tmp),
			hasspaceafter(vars->cmd, vars->tmp - 1));
	return (ft_switch(cmd, vars));
}

int	ft_separator(t_token **cmd, t_vars *vars)
{
	int		x;
	char	save;

	vars->tmp = vars->i;
	x = 0;
	save = vars->cmd[vars->i];
	while (vars->cmd[vars->i] && islimiter(vars->cmd[vars->i]) == 1
		&& ft_isquote(vars->cmd[vars->i]) == 0
		&& ft_isspace(vars->cmd[vars->i]) == 0
		&& x++ < 2 && save == vars->cmd[vars->i])
		vars->i++;
	if (vars->flag == 1)
	{
		(*cmd)->cmd = ft_substr(vars->cmd, vars->tmp, vars->i - vars->tmp);
		(*cmd)->spaceafter = hasspaceafter(vars->cmd, vars->tmp - 1);
		vars->flag = 0;
	}
	else
		ft_newnode(cmd, ft_substr(vars->cmd,
				vars->tmp, vars->i - vars->tmp),
			hasspaceafter(vars->cmd, vars->tmp - 1));
	return (ft_switch(cmd, vars));
}

int	ft_space(t_token **cmd, t_vars *vars)
{
	vars->tmp = vars->i;
	while (vars->cmd[vars->i] && islimiter(vars->cmd[vars->i]) == 0
		&& ft_isquote(vars->cmd[vars->i]) == 0
		&& ft_isspace(vars->cmd[vars->i]) == 1)
		vars->i++;
	return (ft_switch(cmd, vars));
}

int	ft_bracket(t_token **cmd, t_vars *vars)
{
	vars->tmp = vars->i;
	if (vars->cmd[vars->i] == '(' || vars->cmd[vars->i] == ')')
		vars->i++;
	if (vars->flag == 1)
	{
		(*cmd)->cmd = ft_substr(vars->cmd, vars->tmp, vars->i - vars->tmp);
		(*cmd)->spaceafter = hasspaceafter(vars->cmd, vars->tmp - 1);
		vars->flag = 0;
	}
	else
		ft_newnode(cmd, ft_substr(vars->cmd, vars->tmp,
				vars->i - vars->tmp), hasspaceafter(vars->cmd, vars->tmp - 1));
	return (ft_switch(cmd, vars));
}

int	ft_quote(t_token **cmd, t_vars *vars)
{
	char	save;

	vars->tmp = vars->i;
	if (vars->cmd[vars->i] == '\'' || vars->cmd[vars->i] == '"')
		save = vars->cmd[vars->i++];
	while (vars->cmd[vars->i] && vars->cmd[vars->i] != save)
		vars->i++;
	if (vars->cmd[vars->i] == '\'' || vars->cmd[vars->i] == '"')
	{
		vars->i++;
		if (vars->flag == 1)
		{
			(*cmd)->cmd = ft_substr(vars->cmd, vars->tmp, vars->i - vars->tmp);
			(*cmd)->spaceafter = hasspaceafter(vars->cmd, vars->tmp - 1);
			vars->flag = 0;
		}
		else
			new_nodforquotes(cmd, vars, save);
		return (ft_switch(cmd, vars));
	}
	else
		return (wrerror("turboshell:open quotes\n"), 1);
	return (0);
}
