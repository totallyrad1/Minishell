/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_parsing1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:13:33 by asnaji            #+#    #+#             */
/*   Updated: 2024/01/22 12:30:41 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	getlimitertoken1(char c, char f)
{
	if (c == '|')
	{
		if (f == '|')
			return (TOKEN_OR);
		return (TOKEN_PIPE);
	}
	else if (c == '&' && f == '&')
		return (TOKEN_AND);
	else if (c == '$')
		return (TOKEN_DOLLAR);
	else if (c == '(')
		return (TOKEN_OPEN_BRACKET);
	else if (c == ')')
		return (TOKEN_CLOSED_BRACKET);
	return (TOKEN_EXPR);
}

int	getlimitertoken(char c, char f)
{
	if (c == '"')
		return (TOKEN_D_Q);
	else if (c == '\'')
		return (TOKEN_S_Q);
	else if (c == '<')
	{
		if (f == '<')
			return (TOKEN_HEREDOC);
		return (TOKEN_REDIR_IN);
	}
	else if (c == '>')
	{
		if (f == '>')
			return (TOKEN_REDIR_APPEND);
		return (TOKEN_REDIR_OUT);
	}
	return (getlimitertoken1(c, f));
}

int	look_for_char(char *command, int i)
{
	int	flag;

	flag = 0;
	while (command[i] && islimiter(command[i]) == 0 && command[i] != ')')
	{
		if (ft_isspace(command[i]) == 0)
			flag = 1;
		i++;
	}
	return (flag);
}
