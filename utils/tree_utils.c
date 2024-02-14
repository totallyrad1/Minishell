/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 22:25:29 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/14 08:57:09 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static enum e_tree_type	assing_tree_type(enum e_type token_type)
{
	if (token_type == TOKEN_AND)
		return (AND);
	else if (token_type == TOKEN_OR)
		return (OR);
	else if (token_type == TOKEN_PIPE)
		return (PIPE);
	else if (token_type == TOKEN_REDIR_IN)
		return (REDIR_IN);
	else if (token_type == TOKEN_REDIR_OUT)
		return (REDIR_OUT);
	else if (token_type == TOKEN_HEREDOC)
		return (HEREDOC);
	else if (token_type == TOKEN_REDIR_APPEND)
		return (REDIR_APPEND);
	else
		return (CMD);
}

t_tree	*make_node(t_token **cmd, int flag)
{
	t_tree	*newnode;

	newnode = malloc(sizeof(t_tree));
	if (!newnode)
		return (NULL);
	newnode->next = NULL;
	newnode->left = NULL;
	newnode->right = NULL;
	newnode->data = ft_strdup((*cmd)->cmd);
	newnode->tree_type = assing_tree_type((*cmd)->type);
	if (flag)
		(*cmd)->visited = 1;
	return (newnode);
}
