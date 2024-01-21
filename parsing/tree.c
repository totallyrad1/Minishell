/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 22:10:15 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/01/21 22:14:40 by yzaazaa          ###   ########.fr       */
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

static void	skip_brackets(t_cmd **token)
{
	if ((*token)->type == TOKEN_CLOSED_BRACKET)
	{
		while ((*token)->next && (*token)->next->type != TOKEN_OPEN_BRACKET)
			(*token) = (*token)->prev;
	}
	if ((*token)->type == TOKEN_OPEN_BRACKET)
	{
		while ((*token)->prev && (*token)->prev->type != TOKEN_CLOSED_BRACKET)
			(*token) = (*token)->next;
	}
}

t_tree *make_command(t_cmd *token)
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

t_tree *search_pipe(t_cmd *token)
{
	t_cmd	*save;
	t_tree	*node;
	int		is_brackets;
	int		nb_brackets;

	node = NULL;
	if(!token)
		return node;
	is_brackets = 0;
	while(token && token->visited != 1)
	{
		if (token->type == TOKEN_OPEN_BRACKET)
		{
			nb_brackets = 1;
			token->visited = 1;
			is_brackets = 1;
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
		save = token;
		if (token && token->visited != 1 && token->type == TOKEN_CLOSED_BRACKET)
			token->visited = 1;
		if(token && token->visited != 1 && token->type == TOKEN_PIPE)
		{
			node = make_node(&token, 1);
			if (is_brackets)
				node->left = search_logical_operator(token->prev->prev);
			else
				node->left = make_command(token->prev);
			node->right = search_pipe(token->next);
			return (node);
		}
		if (token)
			token = token->next;	
	}
	if (is_brackets)
		return (search_logical_operator(save->prev));
	return (make_command(save));
}

t_tree *search_logical_operator(t_cmd *token)
{
	t_cmd *save;
	t_tree *node;
	int		nb_brackets;

	node = NULL;
	while(token && token->visited != 1)
	{
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
		save = token;
		if (token && token->visited != 1 && token->type == TOKEN_OPEN_BRACKET)
			token = token->prev;
		if(token && token->visited != 1
			&& (token->type == TOKEN_AND || token->type == TOKEN_OR))
		{
			node = make_node(&token, 1);
			node->right = search_pipe(token->next);
			node->left = search_logical_operator(token->prev);
			return (node);
		}
		if (token)
			token = token->prev;
	}
	return (search_pipe(save));
}
