/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 18:07:51 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/21 21:02:44 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_key(char *line)
{
	int		i;
	char	*key;

	i = 0;
	while (line[i] && line[i] != '=' && line[i] != '+')
		i++;
	key = ft_substr(line, 0, i);
	return (key);
}

static char	*get_value(char *line)
{
	int		i;
	int		tmp;
	char	*value;

	i = 0;
	while (line[i] && line[i] != '=')
		i++;
	if (line[i])
		i++;
	else
		return (NULL);
	tmp = i;
	while (line[i])
		i++;
	value = ft_substr(line, tmp, i - tmp);
	return (value);
}

static int	check_arg(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (0);
	i++;
	while (str[i] && str[i] != '=' && str[i] != '+')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	if (str[i] && str[i] != '+' && str[i] != '=')
		return (0);
	return (1);
}

static void	exec_export(char **args, t_env **env, int i)
{
	char	*key;
	char	*value;
	t_env	*tmp;

	key = get_key(args[i]);
	value = get_value(args[i]);
	if (value || ft_strchr(args[i], '='))
	{
		tmp = *env;
		while (tmp)
		{
			if (!ft_strcmp(key, tmp->key))
			{
				if (ft_strchr(args[i], '+'))
					tmp->value = ft_strjoin(tmp->value, value);
				else
					tmp->value = ft_strdup(value);
				break ;
			}
			tmp = tmp->next;
		}
	}
	if (!key_exist_env(*env, key))
		add_env(env, ft_strdup(key), ft_strdup(value));
}

int	ft_export(char **args, t_env **env)
{
	int		i;
	int		arg_fail;

	i = 1;
	arg_fail = 0;
	if (!args[i])
		print_env(*env, 0);
	while (args[i])
	{
		if (!check_arg(args[i]))
		{
			write(2, "export: `", 9);
			write(2, args[i], ft_strlen(args[i]));
			write(2, "': not a valid identifier\n", 26);
			arg_fail = 1;
		}
		else
			exec_export(args, env, i);
		i++;
	}
	exitstatus(arg_fail, 1);
	return (0);
}
