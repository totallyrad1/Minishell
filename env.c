/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:00:51 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/01/31 17:46:17 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*make_env(char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->size = 0;
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

static int	ft_strlen_till(char *str, char c)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != c)
		i++;
	return (i);
}

void	add_env(t_env **env, char *key, char *value)
{
	t_env	*new;
	t_env	*tmp;

	new = make_env(key, value);
	if (!new)
		return ;
	if (!*env)
	{
		*env = new;
		return ;
	}
	tmp = *env;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
	(*env)->size++;
}

static t_env	*get_env()
{
	t_env	*env;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	env = make_env(ft_strdup("PWD"), pwd);
	add_env(&env, ft_strdup("_"), ft_strdup("/usr/bin/env"));
	add_env(&env, ft_strdup("SHLVL"), ft_strdup("1"));
	return (env);
}

t_env	*arr_to_env(char **env)
{
	int		i;
	t_env	*env_lst;
	int		len;

	i = 0;
	if (!*env)
		env_lst = get_env();
	else
	{
		i = 0;
		env_lst = NULL;
		while (env[i])
		{
			len = ft_strlen_till(env[i], '=');
			add_env(&env_lst, ft_strdup_len(env[i], len), ft_strdup(env[i] + len + 1));
			i++;
		}
	}
	return (env_lst);
}

char	**env_to_arr(t_env *env)
{
	int		i;
	char	**env_arr;
	char	*tmp;
	t_env *curr;	

	curr = env;
	env_arr = malloc(sizeof(char *) * (env->size + 1));
	if (!env_arr)
		return (NULL);
	i = 0;
	while (i < env->size && curr)
	{
		if (!env_arr)
			ft_free_array(env_arr);
		tmp = ft_strjoin(ft_strdup(curr->key), "=");
		tmp = ft_strjoin(tmp, curr->value);
		env_arr[i] = ft_strdup(tmp);
		free(tmp);
		i++;
		curr = curr->next;
	}
	env_arr[i] = NULL;
	return (env_arr);
}