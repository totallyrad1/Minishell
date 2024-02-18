/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_exist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 22:06:15 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/18 16:39:40 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	key_exist_env(t_env *env, char *key)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (1);
		env = env->next;
	}
	return (0);
}
