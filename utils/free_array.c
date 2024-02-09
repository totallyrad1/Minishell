/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:23:12 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/09 21:33:39 by asnaji           ###   ########.fr       */
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
		// free(array);
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
		{
			printf("key =====>[%s]\n", env->key);
			free(env->key);
		}
		if(env->value != NULL)
		{
			printf("key =====>[%s]\n", env->value);
			free(env->value);
		}
		last = curr;
		curr = curr->next;
		free(last);
	}
}
