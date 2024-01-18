/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 22:10:15 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/01/18 18:26:51 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tree	*make_node(t_cmd **cmd, int flag)
{
	t_tree	*newnode;
	
	newnode = malloc(sizeof(t_tree));
	if(!newnode)
		return (NULL);
	newnode->left = NULL;
	newnode->right = NULL;
	newnode->data = ft_strdup((*cmd)->cmd);
	if((*cmd)->type == TOKEN_AND)
		newnode->tree_type = AND;
	else if((*cmd)->type == TOKEN_OR)
		newnode->tree_type = OR;
	else if((*cmd)->type == TOKEN_PIPE)
		newnode->tree_type = PIPE;
	else if((*cmd)->type == TOKEN_REDIR_IN)
		newnode->tree_type = REDIR_IN;
	else if((*cmd)->type == TOKEN_REDIR_OUT)
		newnode->tree_type = REDIR_OUT;
	else if((*cmd)->type == TOKEN_HEREDOC)
		newnode->tree_type = HEREDOC;
	else if((*cmd)->type == TOKEN_REDIR_APPEND)
		newnode->tree_type = REDIR_APPEND;
	else
		newnode->tree_type = CMD;
	if (flag)
		(*cmd)->visited = 1;
	return newnode;
}

static int	is_redirection(t_cmd *token)
{
	if (token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT
	|| token->type == TOKEN_HEREDOC || token->type == TOKEN_REDIR_APPEND)
		return (1);
	return (0);
}

void	add_right_child(t_tree **node, t_cmd **token, int flag)
{
	t_tree	*new_node;

	new_node = make_node(token, flag);
	if (!new_node)
		return ;
	(*node)->right = new_node;
}

t_tree *command(t_cmd *token)
{
	t_tree	*root;
	t_tree	*node;
	int		flag;

	while (token->prev && token->prev->visited != 1)
		token = token->prev;
	flag = 0;
	if (token && is_redirection(token))
	{
		node = make_node(&token, 0);
		flag = 1;
	}
	else if (token && token->type == TOKEN_EXPR)
	{
		node= make_node(&token, 0);
		flag = 0;
	}
	root = node;
	token = token->next;
	while (token && token->visited != 1)
	{
		if (flag)
		{
			add_right_child(&node, &token, 0);
			node = node->right;
			token = token->next;
		}
		while (token && token->visited != 1 && token->type == TOKEN_EXPR)
		{
			node->data = ft_strjoin(node->data, " ");
			node->data = ft_strjoin(node->data, token->cmd);
			token = token->next;
		}
		if (token && token->visited != 1 && is_redirection(token))
		{
			add_right_child(&node, &token, 0);
			flag = 1;
			node = node->right;
			token = token->next;
		}
	}
	return (root);
}

t_tree *pipeew(t_cmd *token)
{
	t_cmd *save;
	t_tree *node;


	node = NULL;
	if(!token)
		return node;
	while(token && token->visited != 1)
	{
		save = token;
		if(token->type == TOKEN_PIPE)
		{
			node = make_node(&token, 1);
			node->left = command(token->prev);
			node->right = pipeew(token->next);
			return (node);
		}
		token = token->next;	
	}
	return command(save);
}

t_tree *andor(t_cmd *token)
{
	t_cmd *save;
	t_tree *node;

	node = NULL;
	while(token && token->visited != 1)
	{
		save = token;
		if(token->type == TOKEN_AND || token->type == TOKEN_OR)
		{
			node = make_node(&token, 1);
			node->right = pipeew(token->next);
			node->left = andor(token->prev);
			return (node);
		}
		token = token->prev;
	}
	return pipeew(save);
}
