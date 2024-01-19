/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 18:04:53 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/01/19 17:13:54 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char **ft_cd(char *dir, char **env)
{
	char *old_path;
	char *new_pwd;
	char *new_var;
	char *new_var1;

	old_path = (char *)malloc(5000);
	new_pwd = (char *)malloc(5000);
	if(getcwd(old_path, 5000) == NULL)
		return (perror("getcwd"), free(old_path), env);
	if (chdir(dir) != 0)
		return (perror("chdir"),free(old_path), env);
	if(getcwd(new_pwd, 5000) == NULL)
		return (perror("getcwd"),free(old_path), free(new_pwd), env);
	new_var = ft_strjoin(ft_strdup(""), "OLDPWD");
	new_var = ft_strjoin(new_var, "=");
	new_var = ft_strjoin(new_var, old_path);
	printf("%s\n", new_var);
	env = ft_export(env, new_var, 1);
	free(new_var);
	new_var1 = ft_strjoin(ft_strdup(""), "PWD");
	new_var1 = ft_strjoin(new_var1, "=");
	new_var1 = ft_strjoin(new_var1, new_pwd);
	printf("%s\n", new_var1);
	env = ft_export(env, new_var1, 1);
	free(new_var1);
	free(new_pwd);
	free(old_path);
	return env;
}
