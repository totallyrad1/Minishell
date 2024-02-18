/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_arr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 22:06:34 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/18 16:38:43 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**env_to_arr(t_env *env)
{
	int		i;
	char	**env_arr;
	char	*tmp;
	t_env	*curr;	

	curr = env->next;
	env_arr = rad_malloc(sizeof(char *) * (env->size + 1), 0, ENV);
	if (!env_arr)
		return (NULL);
	i = 0;
	while (i < env->size && curr)
	{
		tmp = ft_strjoin(ft_strdup(curr->key), "=");
		tmp = ft_strjoin(tmp, curr->value);
		env_arr[i] = ft_strdup(tmp);
		i++;
		curr = curr->next;
	}
	env_arr[i] = NULL;
	return (env_arr);
}
