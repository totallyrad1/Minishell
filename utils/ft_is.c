/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 14:59:54 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/20 23:56:56 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_alphanum(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c >= '0' && c <= '1')
		return (1);
	if (c == '_')
		return (1);
	return (0);
}

int	ft_isspace(char c)
{
	if (c == 32 || c == '\t')
		return (1);
	if (c >= 9 && c <= 13)
		return (1);
	return (0);
}

int	ft_isquote(char c)
{
	if (c == '"' || c == '\'')
		return (1);
	return (0);
}

int	islimiter(int c)
{
	if (c == '<' || c == '>')
		return (1);
	if (c == '$' || c == '|' || c == '&')
		return (1);
	return (0);
}

int	islimiter1(int c)
{
	if (c == '<' || c == '>')
		return (1);
	if (c == '|' || c == '&')
		return (1);
	return (0);
}
