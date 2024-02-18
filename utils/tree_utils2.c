/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 22:42:40 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/18 20:30:26 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*skip_brackets_next(t_token *token, int *is_brackets)
{
	int	nb_brackets;

	if (token->type == TOKEN_OPEN_BRACKET)
	{
		nb_brackets = 1;
		token->visited = 1;
		if (is_brackets)
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

t_token	*skip_brackets_prev(t_token *token)
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
