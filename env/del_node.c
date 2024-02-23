/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 22:04:52 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/23 15:51:46 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	del_node_env(t_env **env, char *key)
{
	t_env	*node_to_del;

	node_to_del = get_node_env(*env, key);
	if (!(*env) || !node_to_del)
		return ;
	if (*env == node_to_del)
		*env = node_to_del->next;
	if (node_to_del->next)
		node_to_del->next->prev = node_to_del->prev;
	if (node_to_del->prev)
		node_to_del->prev->next = node_to_del->next;
}
