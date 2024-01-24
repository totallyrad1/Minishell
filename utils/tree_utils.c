/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 22:25:29 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/01/24 06:03:22 by yzaazaa          ###   ########.fr       */
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

void	add_right_child(t_tree **node, t_token **token, int flag)
{
	t_tree	*new_node;

	new_node = make_node(token, flag);
	if (!new_node)
		return ;
	(*node)->right = new_node;
}

t_tree	*check_token(t_token **token, int *flag)
{
	t_tree	*node;

	node = NULL;
	while ((*token)->prev && ((*token)->prev->visited != 1 || (((*token)->prev->visited == 1 && ((*token)->prev->type == TOKEN_CLOSED_BRACKET || (*token)->prev->type == TOKEN_OPEN_BRACKET)))))
		*token = (*token)->prev;
	if (*token && is_redirection(*token))
	{
		node = make_node(token, 0);
		node->next = make_cmd(*token);
		*flag = 1;
	}
	else if (*token && (*token)->type == TOKEN_EXPR)
	{
		node = make_node(token, 0);
		node->next = make_cmd(*token);
		*flag = 0;
	}
	*token = (*token)->next;
	return (node);
}

void	join_data(t_cmd *cmd, t_token **token)
{
	while (cmd->next)
		cmd = cmd->next;
	while (*token && (((*token)->visited != 1 && (*token)->type == TOKEN_EXPR) || ((*token)->visited == 1 && ((*token)->type == TOKEN_CLOSED_BRACKET || (*token)->type == TOKEN_OPEN_BRACKET))))
	{
		if ((*token)->type == TOKEN_CLOSED_BRACKET || (*token)->type == TOKEN_OPEN_BRACKET)
			*token = (*token)->next;
		if (*token)
		{
			cmd->cmd = ft_strjoin(cmd->cmd, " ");
			cmd->cmd = ft_strjoin(cmd->cmd, (*token)->cmd);
			*token = (*token)->next;
		}
	}
}
