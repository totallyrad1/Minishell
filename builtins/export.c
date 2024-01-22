/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 18:07:51 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/01/22 12:00:48 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_key(char *line)
{
	int		i;
	char	*key;

	i = 0;
	while (line[i] && line[i] != '=')
		i++;
	key = ft_substr(line, 0, i);
	return (key);
}

char	*get_value(char *line)
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

char	**create_new_env(char *value, char *var_name, char **env)
{
	int		env_size;
	char	**new_env;
	int		i;
	char	*new_var;

	env_size = 0;
	i = 0;
	while (env[env_size])
		env_size++;
	new_env = malloc((env_size + 2) * (sizeof(char *)));
	while (env[i])
	{
		new_env[i] = env[i];
		i++;
	}
	new_var = ft_strjoin(var_name, "=");
	new_var = ft_strjoin(new_var, value);
	new_env[i++] = new_var;
	new_env[i] = NULL;
	return (free(value), new_env);
}

char	**append_new_env_var_value(char *value, char *var_name, char **env)
{
	char	*new_var;
	int		i;

	i = 0;
	while (env[i] && ft_strncmp(var_name, env[i], ft_strlen(var_name)))
		i++;
	new_var = ft_strjoin(var_name, "=");
	if (value)
		new_var = ft_strjoin(new_var, value);
	env[i] = new_var;
	return (free(value), env);
}

void	printfenv(char **env)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (env[i])
	{
		j = 0;
		printf("declare -x ");
		while (env[i][j] && env[i][j] != '=')
			printf("%c", env[i][j++]);
		printf("\"");
		while (env[i][j])
			printf("%c", env[i][j++]);
		printf("\"");
		i++;
	}
}

char	**ft_export(char **env, char *variable, int flag)
{
	char	*var_name;
	char	*value;

	if (flag == 1)
	{
		var_name = get_key(variable);
		value = get_value(variable);
		if (getenv(var_name) == NULL)
			return (create_new_env(value, var_name, env));
		else
			return (append_new_env_var_value(value, var_name, env));
	}
	printfenv(env);
	return (env);
}
