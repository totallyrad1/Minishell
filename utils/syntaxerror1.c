/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxerror1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:16:01 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/23 17:50:03 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	delimitercheck(char *token)
{
	if (token[0] == '&' && token[1] == '&' && token[2] == '\0')
		return (1);
	if ((token[0] == '|' && token[1] == '|' && token[2] == '\0' )
		|| (token[0] == '|' && token[1] == '\0'))
		return (1);
	if ((token[0] == '<' && token[1] == '<' && token[2] == '\0')
		|| (token[0] == '<' && token[1] == '\0'))
		return (1);
	if ((token[0] == '>' && token[1] == '>' && token[2] == '\0')
		|| (token[0] == '>' && token[1] == '\0'))
		return (1);
	return (0);
}

int	check_limiterssyntax(t_token *curr, int initflag)
{
	if ((islimiter1(curr->cmd[0]) && delimitercheck(curr->cmd) == 0)
		|| (islimiter1(curr->cmd[0]) && !curr->next)
		|| (isredirection(curr->cmd[0]) && curr->next->cmd == NULL)
		|| (islimiter2(curr->cmd[0]) && initflag == 0)
		|| (islimiter2(curr->cmd[0]) && islimiter2(curr->next->cmd[0]))
		|| (isredirection(curr->cmd[0]) && isredirection(curr->next->cmd[0]))
		|| (isredirection(curr->cmd[0]) && islimiter1(curr->next->cmd[0]))
		|| (islimiter1(curr->cmd[0]) && (curr->next->cmd[0] == ')'))
		|| (isredirection(curr->cmd[0]) && (curr->next->cmd[0] == ')'
				|| curr->next->cmd[0] == '(')))
	{
		exitstatus(258, 1);
		return (printf("turboshell: parse error near `%s'\n", curr->cmd), 0);
	}
	return (1);
}

void	init_vars(t_syntax **vars)
{
	*vars = rad_malloc(sizeof(t_syntax), 0, COMMAND);
	(*vars)->closedc = 0;
	(*vars)->openc = 0;
	(*vars)->initflag = 0;
}
