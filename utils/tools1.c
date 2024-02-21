/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:13:58 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/21 16:33:20 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exitstatus(int newstatus, int flag)
{
	static int	status;

	if (flag == 1)
		status = newstatus;
	return (status);
}

int	hasspaceafter(char *str, int i)
{
	if (i == -1)
		return (0);
	if (ft_isspace(str[i]) == 1)
		return (1);
	return (0);
}

void	new_nodforquotes(t_token **cmd, t_vars *vars, char save)
{
	if (save == '"')
		ft_newnode(cmd, ft_substr(vars->cmd,
				vars->tmp, vars->i - vars->tmp),
			hasspaceafter(vars->cmd, vars->tmp - 1));
	else
		ft_newnode(cmd, ft_substr(vars->cmd,
				vars->tmp, vars->i - vars->tmp),
			hasspaceafter(vars->cmd, vars->tmp - 1));
}
