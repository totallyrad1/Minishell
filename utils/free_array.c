/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:23:12 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/14 10:52:36 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	if(array)
	{
		while (array[i])
		{
			free(array[i]);
			i++;
		}
		free(array);
	}
}

void free_env(t_env *env)
{
	t_env *curr;
	t_env *last;

	curr = env;
	while(curr)
	{
		if(env->key != NULL)
			free(env->key);
		if(env->value != NULL)
			free(env->value);
		last = curr;
		curr = curr->next;
		free(last);
	}
}
