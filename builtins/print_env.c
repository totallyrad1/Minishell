/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 15:34:02 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/22 18:30:59 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_all(t_env *env)
{
	while (env)
	{
		printf("declare -x %s", env->key);
		if (env->value)
			printf("=\"%s\"", env->value);
		printf("\n");
		env = env->next;
	}
}

static void	print_export(t_env *env, t_env *head)
{
	if (head->env_null)
	{
		while (env)
		{
			if (!ft_strcmp(env->key, "_") || !ft_strcmp(env->key, "PATH"))
				env = env->next;
			else
			{
				printf("declare -x %s", env->key);
				if (env->value)
					printf("=\"%s\"", env->value);
				printf("\n");
				env = env->next;
			}
		}
	}
	else
		print_all(env);
}

static void	print_env_value(t_env **env)
{
	printf("%s=", env->key);
	printf("%s\n", env->value);
	env = env->next;
}

void	print_env(t_env *env, int flag)
{
	t_env	*head;

	head = env;
	env = env->next;
	if (flag)
	{
		while (env)
		{
			if (env->value)
			{
				if (head->env_null && !ft_strcmp(env->key, "PATH"))
					env = env->next;
				else
					print_env_value(&env);
			}
			else
				env = env->next;
		}
	}
	else
		print_export(env, head);
	exitstatus(0, 1);
}
