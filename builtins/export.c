/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 18:07:51 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/16 00:04:13 by yzaazaa          ###   ########.fr       */
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
	i++;
	tmp = i;
	while (line[i])
		i++;
	value = ft_substr(line, tmp, i - tmp);
	return (value);
}

static void	printfenv(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	tmp = tmp->next;
	while (tmp)
	{
		write(1, "declare -x ", 11);
		write(1, tmp->key, ft_strlen(tmp->key));
		if (tmp->value)
		{
			write(1, "=\"", 2);
			write(1, tmp->value, ft_strlen(tmp->value));
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		tmp = tmp->next;
	}
}

static int	check_arg(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (0);
	i++;
	while (str[i] && str[i] != '=' && (str[i] != '+' && str[i + 1] != '='))
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	if (!str[i])
		return (2);
	return (1);
}

int	ft_export(char **args, t_env **env)
{
	char	*key;
	char	*value;
	t_env	*tmp;
	int		i;
	int		flag;

	i = 1;
	if (!args[i])
		printfenv(env);
	while (args[i])
	{
		flag = 0;
		if (!check_arg(args[i]))
		{
			write(2, "export: `", 9);
			write(2, args[i], ft_strlen(args[i]));
			write(2, "': not a valid identifier\n", 26);
			exitstatus(1, 1);
		}
		else
		{
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
						{
							// free(tmp->value);
							tmp->value = ft_strdup(value);
						}
						flag = 1;
						break ;
					}
					tmp = tmp->next;
				}
			}
			if (!flag)
				add_env(env, ft_strdup(key), ft_strdup(value));
			// free(key);
			// free(value);
		}
		i++;
	}
	exitstatus(0, 1);
	return (0);
}
