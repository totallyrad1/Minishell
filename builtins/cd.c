/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 18:04:53 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/01/31 17:05:48 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#include "../minishell.h"

char	**ft_cd(char *dir, char **env)
{
	char	*old_path;
	char	*new_pwd;
	char	*new_var;
	char	*new_var1;

	old_path = getcwd(NULL, 0);
	if(!old_path)
		return (perror("getcwd"), free(old_path), env);
	if (chdir(dir) != 0)
		return (perror("chdir"), free(old_path), env);
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return (perror("getcwd"), free(old_path), free(new_pwd), env);
	new_var = ft_strjoin(ft_strdup(""), "OLDPWD");
	new_var = ft_strjoin(new_var, "=");
	new_var = ft_strjoin(new_var, old_path);
	env = ft_export(env, new_var, 1);
	free(new_var);
	new_var1 = ft_strjoin(ft_strdup(""), "PWD");
	new_var1 = ft_strjoin(new_var1, "=");
	new_var1 = ft_strjoin(new_var1, new_pwd);
	env = ft_export(env, new_var1, 1);
	return (free(new_var1), free(new_pwd), free(old_path), env);
}
