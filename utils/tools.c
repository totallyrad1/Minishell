/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:17:14 by asnaji            #+#    #+#             */
/*   Updated: 2024/01/13 17:50:29 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	ft_newnode(t_cmd **cmd, char *value, int type, int state)
// {
// 	t_cmd	*new_node;
// 	t_cmd	*curr;

// 	new_node = malloc(sizeof(t_cmd));
// 	if (!new_node)
// 		exit(0);
// 	curr = *cmd;
// 	new_node->next = NULL;
// 	new_node->cmd = value;
// 	new_node->state = state;
// 	new_node->type = type;
// 	while (curr->next)
// 		curr = curr->next;
// 	curr->next = new_node;
// }

void	ft_free_cmd(t_cmd *lst)
{
	t_cmd	*curr;
	t_cmd	*lastnode;

	if(!lst)
		return ;
	curr = lst;
	while (curr)
	{
		lastnode = curr;
		if (curr)
			curr = curr->next;
		else
		 	break;
		free(lastnode->cmd);
		free(lastnode);
	}
}
