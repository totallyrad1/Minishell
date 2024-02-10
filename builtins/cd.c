/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 18:04:53 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/10 22:07:18 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	chdir_home(char **args, t_env **env)
{
	if (!args[1] || !ft_strcmp(args[1], "~"))
	{
		if (!get_value_env(*env, "HOME"))
		{
			write(2, "cd: HOME not set\n", 17);
			exitstatus(1, 1);
			return (0);
		}
		change_value_env(env, "OLDPWD", ft_strdup((*env)->pwd));
		free((*env)->pwd);
		(*env)->pwd = getcwd(NULL, 0);
		change_value_env(env, "PWD", (*env)->pwd);
		return (1);
	}
	return (0);
}

int	dir_not_found(char **args)
{
	if (chdir(args[1]) == -1)
	{
		write(2, "cd: ", 4);
		write(2, args[1], ft_strlen(args[1]));
		write(2, ": No such file or directory\n", 28);
		exitstatus(1, 1);
		return (1);
	}
	return (0);
}

char	*get_points(char *str)
{
	int		i;
	int		j;

	i = 0;
	while (str[i] && str[i] != '.')
		i++;
	j = i;
	while (str[j] && str[j] == '.')
		j++;
	return (ft_substr(str, i, j - i));
}

int	dir_removed(char **args, t_env **env, char *dir)
{
	char	*points;

	if (!dir)
	{
		write(2, "cd: error retrieving current directory:", 39);
		write(2, " getcwd: cannot access parent directories:", 42);
		write(2, " No such file or directory\n", 27);
		exitstatus(1, 1);
		dir = ft_strjoin(ft_strdup((*env)->pwd), "/");
		points = get_points(args[1]);
		dir = ft_strjoin(dir, points);
		free(points);
		change_value_env(env, "OLDPWD", ft_strdup((*env)->pwd));
		free((*env)->pwd);
		(*env)->pwd = dir;
		change_value_env(env, "PWD", ft_strdup(dir));
		return (1);
	}
	return (0);
}

int	chdir_dash(char **args, t_env **env)
{
	if (!ft_strcmp(args[1], "-"))
	{
		if (chdir(get_value_env(*env, "OLDPWD")) == -1)
		{
			write(2, "cd: OLDPWD not set\n", 19);
			exitstatus(1, 1);
			return (0);
		}
		change_value_env(env, "OLDPWD", ft_strdup((*env)->pwd));
		free((*env)->pwd);
		(*env)->pwd = getcwd(NULL, 0);
		change_value_env(env, "PWD", (*env)->pwd);
		get_pwd(*env);
		return (1);
	}
	return (0);
}

int	ft_cd(char **args, t_env **env)
{
	char	*dir;

	if (args[1] && args[2])
	{
		write(2, "cd: too many arguments\n", 24);
		return (0);
	}
	if (chdir_home(args, env))
		return (0);
	if (chdir_dash(args, env))
		return (0);
	if (dir_not_found(args))
		return (0);
	dir = getcwd(NULL, 0);
	if (dir_removed(args, env, dir))
		return (0);
	if (!ft_strcmp(dir, (*env)->pwd))
	{
		change_value_env(env, "OLDPWD", ft_strdup((*env)->pwd));
		free(dir);
		return (0);
	}
	change_value_env(env, "OLDPWD", ft_strdup((*env)->pwd));
	free((*env)->pwd);
	(*env)->pwd = dir;
	change_value_env(env, "PWD", ft_strdup(dir));
	return (0);
}
