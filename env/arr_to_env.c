/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_to_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 22:07:12 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/17 22:16:03 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_number(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] && (str[i] == '-' || str[i] == '+'))
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i])
		return (0);
	return (1);
}

static int	ft_strlen_till(char *str, char c)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != c)
		i++;
	return (i);
}

static char	*check_shlvl(char *key, char *value)
{
	int	shlvl;

	if (!ft_strcmp(key, "SHLVL"))
	{
		if (is_number(value))
		{
			shlvl = ft_atoi(value);
			if (shlvl == 999)
				value = NULL;
			else if (shlvl > 999)
				value = ft_itoa(1);
			else if (shlvl < 0)
				value = ft_itoa(0);
			else
				value = ft_itoa(shlvl + 1);
		}
		else
			value = ft_itoa(1);
	}
	return (value);
}

t_env	*arr_to_env(char **env)
{
	int		i;
	t_env	*env_lst;
	int		len;
	char	*key;
	char	*value;

	i = 0;
	if (!*env)
		env_lst = get_env();
	else
	{
		i = -1;
		env_lst = make_env(NULL, NULL);
		env_lst->pwd = getcwd(NULL, 0);
		while (env[++i])
		{
			len = ft_strlen_till(env[i], '=');
			key = ft_strdup_len(env[i], len);
			value = ft_strdup(env[i] + len + 1);
			value = check_shlvl(key, value);
			add_env(&env_lst, key, value);
		}
	}
	return (env_lst);
}
