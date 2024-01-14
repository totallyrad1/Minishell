/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 15:27:25 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/01/13 18:02:45 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**unset(char **envp, char *var)
{
	int		size_envp;
	int		i;
	int		index_line_var;
	char	**new_env;

	size_envp = 0;
	index_line_var = 0;
	while(envp[size_envp])
	{
		if(!ft_strncmp(var, envp[size_envp], ft_strlen(var)))
			index_line_var = size_envp;
		size_envp++;
	}
	new_env = malloc(sizeof(char *) * size_envp);
	if (!new_env)
		exit(1);
	i = 0;
	while (i < size_envp)
	{
		if (i != index_line_var)
			new_env[i] = ft_strdup(envp[i]);
		i++;
	}
	new_env[i] = NULL;
	ft_free_array(envp);
	return (new_env);
}