/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 22:25:29 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/01/21 23:00:27 by yzaazaa          ###   ########.fr       */
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

t_tree	*make_node(t_cmd **cmd, int flag)
{
	t_tree	*newnode;

	newnode = malloc(sizeof(t_tree));
	if (!newnode)
		return (NULL);
	newnode->left = NULL;
	newnode->right = NULL;
	newnode->data = ft_strdup((*cmd)->cmd);
	newnode->tree_type = assing_tree_type((*cmd)->type);
	if (flag)
		(*cmd)->visited = 1;
	return (newnode);
}

void	add_right_child(t_tree **node, t_cmd **token, int flag)
{
	t_tree	*new_node;

	new_node = make_node(token, flag);
	if (!new_node)
		return ;
	(*node)->right = new_node;
}

t_tree	*check_token(t_cmd **token, int *flag)
{
	t_tree	*node;

	node = NULL;
	while ((*token)->prev && (*token)->prev->visited != 1)
		*token = (*token)->prev;
	if (*token && is_redirection(*token))
	{
		node = make_node(token, 0);
		*flag = 1;
	}
	else if (*token && (*token)->type == TOKEN_EXPR)
	{
		node = make_node(token, 0);
		*flag = 0;
	}
	*token = (*token)->next;
	return (node);
}

void	join_data(t_tree *node, t_cmd **token)
{
	while (*token && (*token)->visited != 1 && (*token)->type == TOKEN_EXPR)
	{
		node->data = ft_strjoin(node->data, " ");
		node->data = ft_strjoin(node->data, (*token)->cmd);
		*token = (*token)->next;
	}
}
