/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_null.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 22:12:49 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/22 18:31:10 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*get_env(void)
{
	t_env	*env;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	env = make_env(NULL, NULL);
	env->pwd = pwd;
	env->env_null = 1;
	add_env(&env, ft_strdup("PATH"),
		ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:."));
	add_env(&env, ft_strdup("OLDPWD"), NULL);
	add_env(&env, ft_strdup("PWD"), ft_strdup(env->pwd));
	add_env(&env, ft_strdup("_"), ft_strdup("/usr/bin/env"));
	add_env(&env, ft_strdup("SHLVL"), ft_strdup("1"));
	return (env);
}
