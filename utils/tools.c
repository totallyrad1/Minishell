/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:17:14 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/21 21:33:29 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_newnode(t_token **cmd, char *value, int spaceafter)
{
	t_token	*new_node;
	t_token	*curr;

	new_node = rad_malloc(sizeof(t_token), 0, COMMAND);
	curr = *cmd;
	new_node->visited = 0;
	new_node->spaceafter = spaceafter;
	new_node->next = NULL;
	new_node->cmd = value;
	while (curr->next)
		curr = curr->next;
	curr->next = new_node;
	new_node->prev = curr;
}

t_token	*init_token(void)
{
	t_token	*cmd;

	cmd = rad_malloc(sizeof(t_token), 0, COMMAND);
	cmd->visited = 0;
	cmd->spaceafter = 0;
	cmd->next = NULL;
	cmd->cmd = NULL;
	cmd->prev = NULL;
	return (cmd);
}

void	wrerror(char *str)
{
	if (str)
		write(2, str, ft_strlen(str));
}
