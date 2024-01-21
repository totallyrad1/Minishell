/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_brackets.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 22:42:40 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/01/21 22:59:41 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*skip_brackets_next(t_cmd *token, int *is_brackets)
{
	int	nb_brackets;

	if (token->type == TOKEN_OPEN_BRACKET)
	{
		nb_brackets = 1;
		token->visited = 1;
		*is_brackets = 1;
		token = token->next;
		while (token && token->visited != 1 && nb_brackets)
		{
			if (token->type == TOKEN_OPEN_BRACKET)
				nb_brackets++;
			else if (token->type == TOKEN_CLOSED_BRACKET)
				nb_brackets--;
			if (!nb_brackets)
				break ;
			token = token->next;
		}
	}
	return (token);
}

t_cmd	*skip_brackets_prev(t_cmd *token)
{
	int	nb_brackets;

	if (token->type == TOKEN_CLOSED_BRACKET)
	{
		nb_brackets = 1;
		token = token->prev;
		while (token && token->visited != 1 && nb_brackets)
		{
			if (token->type == TOKEN_OPEN_BRACKET)
				nb_brackets--;
			else if (token->type == TOKEN_CLOSED_BRACKET)
				nb_brackets++;
			if (!nb_brackets)
				break ;
			token = token->prev;
		}
	}
	return (token);
}
