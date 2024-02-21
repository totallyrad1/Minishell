/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxerror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:57:36 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/21 17:26:18 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_flags(t_token *curr, t_syntax **vars)
{
	if (curr->type != TOKEN_CLOSED_BRACKET
		&& curr->type != TOKEN_OPEN_BRACKET
		&& curr->cmd
		&& isredirection(curr->cmd[0]) == 0
		&& islimiter2(curr->cmd[0]) == 0)
		(*vars)->initflag = 1;
	if (curr->type == TOKEN_CLOSED_BRACKET)
		(*vars)->closedc++;
	else if (curr->type == TOKEN_OPEN_BRACKET)
		(*vars)->openc++;
}

int	check_bracketssyntax(t_token *curr, t_syntax *vars)
{
	if ((vars->initflag == 0 && curr->cmd[0] == ')')
		|| (isredirection(curr->cmd[0]) && curr->next
			&& curr->next->cmd[0] == '(')
		|| (curr->cmd[0] == ')' && curr->next
			&& islimiter2(curr->next->cmd[0]) == 0)
		|| (curr->cmd[0] == '(' && curr->next
			&& islimiter2(curr->next->cmd[0]))
		|| (curr->cmd[0] == '(' && curr->next
			&& curr->next->cmd[0] == ')')
		|| (islimiter2(curr->cmd[0]) == 0
			&& curr->next && curr->next->cmd[0] == '('))
	{
		exitstatus(258, 1);
		printf("syntax error near unexpected token `%s'\n", curr->cmd);
		return (0);
	}
	return (1);
}

int	checkopenandclosed(t_syntax *vars)
{
	if (heredocendedwith_c(0, 0) == 1 && vars->openc != vars->closedc)
	{
		exitstatus(258, 1);
		return (printf("brackets syntax error\n"), 0);
	}
	return (1);
}

int	check_syntax_error(t_token **cmd)
{
	t_token		*curr;
	t_syntax	*vars;

	curr = *cmd;
	init_vars(&vars);
	while (curr && heredocendedwith_c(0, 0) == 0)
	{
		set_flags(curr, &vars);
		if (check_limiterssyntax(curr, vars->initflag) == 0)
			return (0);
		if (check_bracketssyntax(curr, vars) == 0)
			return (0);
		if (delimitercheck(curr->cmd) == 1 && curr->cmd
			&& curr->cmd[0] == '<' && curr->cmd[1] == '<'
			&& curr->cmd[2] == '\0'
			&& curr->next && curr->next->cmd)
		{
			curr->heredocfd = heredocshit(curr->next->cmd);
			curr->for_heredoc = curr->next->for_heredoc;
		}
		curr = curr->next;
	}
	return (checkopenandclosed(vars));
}
