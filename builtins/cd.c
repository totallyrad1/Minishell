/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 18:04:53 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/06 17:09:49 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd(char **args, t_env **env)
{
	char	*dir;
	char	*old_path;
	char	*new_pwd;
	char	*new_var;
	char *test[3];

	dir = args[1];
	old_path = getcwd(NULL, 0);
	if(!old_path)
		return (perror("getcwd"), free(old_path), 0);
	if (chdir(dir) != 0)
		return (perror("chdir"), free(old_path), 0);
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return (perror("getcwd"), free(old_path), free(new_pwd), 0);
	new_var = ft_strjoin(ft_strdup(""), "OLDPWD");
	new_var = ft_strjoin(new_var, "=");
	new_var = ft_strjoin(new_var, old_path);
	test[0] = "export";
	test[1] = new_var;
	test[2] = NULL;
	ft_export(test, env);
	free(new_var);
	new_var = ft_strjoin(ft_strdup(""), "PWD");
	new_var = ft_strjoin(new_var, "=");
	new_var = ft_strjoin(new_var, new_pwd);
	test[0] = "export";
	test[1] = new_var;
	test[2] = NULL;
	ft_export(test, env);
	return (free(new_var), free(new_pwd), free(old_path), 0);
}
