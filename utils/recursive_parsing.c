/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:05:06 by asnaji            #+#    #+#             */
/*   Updated: 2024/01/31 15:11:29 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int hasspaceafter(char *str, int i)
{
	if(str[i + 1] == 32)
		return 1;
	return 0;
}

int	ft_char(t_token **cmd, t_vars *vars)
{
	vars->tmp = vars->i;
	while (vars->cmd[vars->i] && islimiter(vars->cmd[vars->i]) == 0
		&& ft_isquote(vars->cmd[vars->i]) == 0 && ft_isspace(vars->cmd[vars->i]) == 0
		&& (vars->cmd[vars->i] != ')' && vars->cmd[vars->i] != '('))
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

int	ft_separator(t_token **cmd, t_vars *vars)
{
	int		x;
	char	save;

	vars->tmp = vars->i;
	x = 0;
	save = vars->cmd[vars->i];
	while (vars->cmd[vars->i] && islimiter(vars->cmd[vars->i]) == 1
		&& ft_isquote(vars->cmd[vars->i]) == 0
		&& ft_isspace(vars->cmd[vars->i]) == 0 && x++ < 2 && save == vars->cmd[vars->i])
		vars->i++;
	if (islimiter(vars->cmd[vars->i]) == 1 || look_for_char(vars->cmd, vars->i) == 0
		|| (vars->cmd[vars->tmp] == '&' && vars->cmd[vars->tmp + 1] != '&'))
		return (printf("syntax error\n"), 1);
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

int	ft_space(t_token **cmd, t_vars *vars)
{
	vars->tmp = vars->i;
	while (vars->cmd[vars->i] && islimiter(vars->cmd[vars->i]) == 0
		&& ft_isquote(vars->cmd[vars->i]) == 0 && ft_isspace(vars->cmd[vars->i]) == 1)
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
		(*cmd)->state = GENERAL;
		(*cmd)->spaceafter = hasspaceafter(vars->cmd, vars->i);
		vars->flag = 0;
	}
	else
		ft_newnode(cmd, ft_substr(vars->cmd, vars->tmp, vars->i - vars->tmp), GENERAL, hasspaceafter(vars->cmd, vars->i));
	return (ft_switch(cmd, vars));
}

int	ft_quote(t_token **cmd, t_vars *vars)
{
	char	save;

	vars->tmp = vars->i + 1;
	if (vars->cmd[vars->i] == '\'' || vars->cmd[vars->i] == '"')
		save = vars->cmd[vars->i++];
	while (vars->cmd[vars->i] && vars->cmd[vars->i] != save)
		vars->i++;
	if (vars->cmd[vars->i] == '\'' || vars->cmd[vars->i] == '"')
	{
		if (vars->flag == 1)
		{
			(*cmd)->cmd = ft_substr(vars->cmd, vars->tmp, vars->i - vars->tmp);
			(*cmd)->spaceafter = hasspaceafter(vars->cmd, vars->i);
			if(save == '"')
				(*cmd)->state = IN_DQUOTE;
			else
			 	(*cmd)->state = IN_QUOTE;;
			vars->flag = 0;
		}
		else
		{
			if(save == '"')
				ft_newnode(cmd, ft_substr(vars->cmd, vars->tmp, vars->i - vars->tmp), IN_DQUOTE, hasspaceafter(vars->cmd, vars->i));
			else
			 	ft_newnode(cmd, ft_substr(vars->cmd, vars->tmp, vars->i - vars->tmp), IN_QUOTE, hasspaceafter(vars->cmd, vars->i));
		}
		return (ft_switch(cmd, vars));
	}
	else
		return (printf("syntax error\n"), 1);
	return (0);
}
