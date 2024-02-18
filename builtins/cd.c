/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 18:04:53 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/18 16:36:13 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	chdir_home(char **args, t_env **env)
{
	if (!args[1] || !ft_strcmp(args[1], "~"))
	{
		if (!key_exist_env(*env, "HOME"))
		{
			wrerror("Turboshell: cd: HOME not set\n");
			exitstatus(1, 1);
			return (1);
		}
		else if (get_value_env(*env, "HOME")[0] != '\0'
			&& chdir(get_value_env(*env, "HOME")) == -1)
		{
			wrerror("Turboshell: cd: ");
			wrerror(get_value_env(*env, "HOME"));
			wrerror(": No such file or directory\n");
			exitstatus(1, 1);
			return (1);
		}
		change_value_env(env, "OLDPWD", ft_strdup((*env)->pwd));
		(*env)->pwd = getcwd(NULL, 0);
		change_value_env(env, "PWD", ft_strdup((*env)->pwd));
		return (1);
	}
	return (0);
}

char	*get_first_dir(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '/')
		i++;
	if (!str[i])
		return (NULL);
	return (ft_strdup_len(str, i));
}

static int	dir_not_found(char **args, t_env **env)
{
	DIR		*dir;

	(void)env;
	dir = opendir(args[1]);
	if (!dir)
	{
		wrerror("Turboshell: cd: ");
		wrerror(args[1]);
		wrerror(": ");
		perror("");
		exitstatus(1, 1);
		return (1);	
	}
	else
		closedir(dir);
	if (chdir(args[1]) == -1)
	{
		wrerror("Turboshell: cd: ");
		wrerror(args[1]);
		wrerror(": ");
		perror("");
		exitstatus(1, 1);
		return (1);
	}
	return (0);
}

static int	dir_removed(char **args, t_env **env, char *dir)
{
	char	*points;

	if (!dir)
	{
		
		wrerror("Turboshell: cd: getcwd: cannot access parent directories: ");
		perror("");
		exitstatus(1, 1);
		dir = ft_strjoin(ft_strdup((*env)->pwd), "/");
		points = get_points(args[1]);
		dir = ft_strjoin(dir, points);
		change_value_env(env, "OLDPWD", ft_strdup((*env)->pwd));
		(*env)->pwd = dir;
		change_value_env(env, "PWD", ft_strdup(dir));
		return (1);
	}
	return (0);
}

static int	chdir_dash(char **args, t_env **env)
{
	if (!ft_strcmp(args[1], "-"))
	{
		if (!get_value_env(*env, "OLDPWD"))
		{
			wrerror("Turboshell: cd: OLDPWD not set\n");
			exitstatus(1, 1);
			return (1);
		}
		else if (chdir(get_value_env(*env, "OLDPWD")) == -1)
		{
			wrerror("Turboshell: ");
			wrerror(get_value_env(*env, "OLDPWD"));
			wrerror(": No such file or directory\n");
			exitstatus(1, 1);
			return (1);
		}
		change_value_env(env, "OLDPWD", ft_strdup((*env)->pwd));
		(*env)->pwd = getcwd(NULL, 0);
		change_value_env(env, "PWD", ft_strdup((*env)->pwd));
		get_pwd(*env);
		return (1);
	}
	return (0);
}

int	ft_cd(char **args, t_env **env)
{
	char	*dir;

	if (args[1] && args[1][0] == '\0')
		return (0);
	if (args[1] && args[2])
	{
		exitstatus(1, 1);
		return (wrerror("Turboshell: cd: too many arguments\n"), 0);
	}
	if (chdir_home(args, env))
		return (0);
	if (chdir_dash(args, env))
		return (0);
	if (dir_not_found(args, env))
		return (0);
	dir = getcwd(NULL, 0);
	if (dir_removed(args, env, dir))
		return (0);
	if (!ft_strcmp(dir, (*env)->pwd))
	{
		change_value_env(env, "OLDPWD", ft_strdup((*env)->pwd));
		return (0);
	}
	change_value_env(env, "OLDPWD", ft_strdup((*env)->pwd));
	(*env)->pwd = dir;
	change_value_env(env, "PWD", ft_strdup(dir));
	return (0);
}
