/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 15:34:02 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/21 21:02:57 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_export(t_env *env, t_env *head)
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
			print_export(env, head);
		env = env->next;
	}
	exitstatus(0, 1);
}
