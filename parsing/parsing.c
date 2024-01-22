/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 19:59:53 by asnaji            #+#    #+#             */
/*   Updated: 2024/01/22 12:19:56 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_switch(t_cmd **cmd, char *command, int flag, int i)
{
	if (command[i])
	{
		if (ft_isspace(command[i]) == 1)
			return (ft_space(cmd, command, flag, i));
		else if (ft_isquote(command[i]) == 1)
			return (ft_quote(cmd, command, flag, i));
		else if (islimiter(command[i]) == 1)
			return (ft_separator(cmd, command, flag, i));
		else if (command[i] == '(' || command[i] == ')')
			return (ft_bracket(cmd, command, flag, i));
		else
			return (ft_char(cmd, command, flag, i));
	}
	return (0);
}

void	give_state_and_type(t_cmd **cmd)
{
	t_cmd	*curr;

	curr = *cmd;
	while (curr)
	{
		curr->type = getlimitertoken(curr->cmd[0], curr->cmd[1]);
		if (curr->cmd[0] == '"')
			curr->state = IN_DQUOTE;
		else if (curr->cmd[0] == '\'')
			curr->state = IN_QUOTE;
		else
			curr->state = GENERAL;
		curr = curr->next;
	}
}
