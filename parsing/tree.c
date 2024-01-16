/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 22:10:15 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/01/16 22:13:01 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <sys/_types/_null.h>
#include <unistd.h>


t_tree *make_node(t_cmd **cmd)
{
	t_tree *newnode;
	
	newnode = malloc(sizeof(t_tree));
	if(!newnode)
		return NULL;
	newnode->left = NULL;
	newnode->right = NULL;
	newnode->data = ft_strdup((*cmd)->cmd);
	if((*cmd)->type == TOKEN_AND)
		newnode->tree_type = AND;
	else if((*cmd)->type == TOKEN_OR)
		newnode->tree_type = OR;
	else if((*cmd)->type == PIPE)
		newnode->tree_type = PIPE;
	else
		newnode->tree_type = CMD;
	(*cmd)->visited = 1;
	return newnode;
}


t_tree *command(t_cmd *token)
{
	t_cmd *save;
	t_tree *node;
	
	if(token)
	{
		node = make_node(&token);
		node->left = NULL;
		node->right = NULL;
	}
	return node;
}

t_tree *pipeew(t_cmd *token)
{
	t_cmd *save;
	t_tree *node;


	node = NULL;
	if(!token)
		return node;
	while(token 
		&& token->visited != 1)
	{
		save = token;
		if(token->type == TOKEN_PIPE)
		{
			node = make_node(&token);
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
			node = make_node(&token);
			node->right = pipeew(token->next);
			node->left = andor(token->prev);
			return (node);
		}
		token = token->prev;
	}
	return pipeew(save);
}

