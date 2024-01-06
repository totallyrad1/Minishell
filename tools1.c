/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 14:59:54 by asnaji            #+#    #+#             */
/*   Updated: 2024/01/06 15:00:18 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_isspace(char c)
{
	if (c == ' ' || c == '\t')
		return 1;
	if(c >= 9 && c <= 13)
		return 1;
	return 0;
}

int ft_isquote(char c)
{
	if (c == '"' || c == '\'')
		return 1;
	return 0;
}

int islimiter(int c)
{
	if (c == '<' || c == '>')
		return 1;
	if (c == '$' || c == '|')
		return 1;
	return 0;
}