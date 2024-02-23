/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 19:59:53 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/23 19:02:06 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_dollarsign(t_token **cmd, t_vars **vars)
{
	(*vars)->tmp = (*vars)->i;
	if ((*vars)->cmd[(*vars)->i] == '$')
		(*vars)->i++;
	if ((*vars)->cmd[(*vars)->i] == '?')
		(*vars)->i++;
	else
		while ((*vars)->cmd[(*vars)->i]
			&& (ft_alphanum((*vars)->cmd[(*vars)->i]) == 1))
			(*vars)->i++;
	if ((*vars)->flag == 1)
	{
		(*cmd)->cmd = ft_substr((*vars)->cmd,
				(*vars)->tmp, (*vars)->i - (*vars)->tmp);
		(*cmd)->spaceafter = hasspaceafter((*vars)->cmd, (*vars)->tmp - 1);
		(*vars)->flag = 0;
	}
	else
		ft_newnode(cmd, ft_substr((*vars)->cmd,
				(*vars)->tmp, (*vars)->i - (*vars)->tmp),
			hasspaceafter((*vars)->cmd, (*vars)->tmp - 1));
	return (0);
}

int	tokenizer(t_token **cmd, t_vars *vars)
{
	int	i;

	i = 0;
	while (vars->cmd[vars->i] && i == 0)
	{
		if (ft_isspace(vars->cmd[vars->i]) == 1)
			i = (ft_space(&vars));
		else if (ft_isquote(vars->cmd[vars->i]) == 1)
			i = (ft_quote(cmd, &vars));
		else if (vars->cmd[vars->i] == '$')
			i = (ft_dollarsign(cmd, &vars));
		else if (islimiter(vars->cmd[vars->i]) == 1)
			i = (ft_separator(cmd, &vars));
		else if (vars->cmd[vars->i] == '(' || vars->cmd[vars->i] == ')')
			i = (ft_bracket(cmd, &vars));
		else
			i = (ft_char(cmd, &vars));
	}
	return (i);
}

void	give_state_and_type(t_token **cmd)
{
	t_token	*curr;

	curr = *cmd;
	while (curr)
	{
		if (curr->cmd && curr->cmd[0])
			curr->type = getlimitertoken(curr->cmd[0], curr->cmd[1]);
		curr = curr->next;
	}
}
