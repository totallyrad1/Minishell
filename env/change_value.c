/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 22:04:17 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/17 22:04:38 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_value_env(t_env **env, char *key, char *value)
{
	t_env	*tmp;
	int		flag;

	flag = 0;
	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			tmp->value = value;
			flag = 1;
			break ;
		}
		tmp = tmp->next;
	}
	if (!flag)
		add_env(env, key, value);
}
