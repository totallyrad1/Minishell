/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:17:14 by asnaji            #+#    #+#             */
/*   Updated: 2024/01/28 15:59:22 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_newnode(t_token **cmd, char *value, int state)
{
	t_token	*new_node;
	t_token	*curr;

	new_node = malloc(sizeof(t_token));
	if (!new_node)
		exit(0);
	curr = *cmd;
	new_node->visited = 0;
	new_node->next = NULL;
	new_node->cmd = value;
	new_node->state = state;
	while (curr->next)
		curr = curr->next;
	curr->next = new_node;
	new_node->prev = curr;
}

void	ft_free_cmd(t_token *lst)
{
	t_token	*curr;
	t_token	*lastnode;

	if (!lst)
		return ;
	curr = lst;
	while (curr)
	{
		lastnode = curr;
		if (curr)
			curr = curr->next;
		else
			break ;
		free(lastnode->cmd);
		free(lastnode);
	}
}
