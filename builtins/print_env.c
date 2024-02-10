/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 15:34:02 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/01/30 20:37:56 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_env(t_env *env)
{
	while (env)
	{
		printf("%s=", env->key);
		if (env->value)
			printf("%s", env->value);
		printf("\n");
		env = env->next;
	}
}
