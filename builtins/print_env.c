/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 15:34:02 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/18 16:37:02 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_env(t_env *env, int flag)
{
	t_env	*head;

	head = env;
	env = env->next;
	while (env)
	{
		if (flag)
		{
			if (env->value)
			{
				printf("%s=", env->key);
				printf("%s\n", env->value);
			}
		}
		else
		{
			if (!ft_strcmp(env->key, "_") && !head->env_null)
			{
				printf("declare -x %s", env->key);
				if (env->value)
					printf("=\"%s\"", env->value);
				printf("\n");
			}
			else if (ft_strcmp(env->key, "_"))
			{
				printf("declare -x %s", env->key);
				if (env->value)
					printf("=\"%s\"", env->value);
				printf("\n");
			}
		}
		env = env->next;
	}
	exitstatus(0, 1);
}
