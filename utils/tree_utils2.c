/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 22:42:40 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/01/24 23:35:01 by yzaazaa          ###   ########.fr       */
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

static void	free_cmd(t_cmd **cmd)
{
	t_cmd	*tmp;

	if (!cmd)
		return ;
	if (!*cmd)
	{
		free(*cmd);
		return ;
	}
	while (*cmd)
	{
		tmp = *cmd;
		*cmd = (*cmd)->next;
		free(tmp->cmd);
		free(tmp);
	}
}

void	free_tree(t_tree **root)
{
	t_tree	*tmp;

	tmp = *root;
	if (tmp->next)
		free_cmd(&tmp->next);
	if (!tmp)
		return ;
	free(tmp->data);
	if (tmp->left)
		free_tree(&tmp->left);
	if (tmp->right)
		free_tree(&tmp->right);
	free(tmp);
	*root = NULL;
}
