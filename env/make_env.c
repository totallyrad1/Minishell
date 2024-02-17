/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 22:14:48 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/17 22:15:10 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*make_env(char *key, char *value)
{
	t_env	*node;

	node = rad_malloc(sizeof(t_env), 0, ENV);
	if (!node)
		return (NULL);
	node->size = 0;
	node->key = key;
	node->value = value;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}
