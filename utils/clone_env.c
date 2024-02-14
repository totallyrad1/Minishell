/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clone_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:16:19 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/14 16:32:19 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_clone_env(char **env)
{
	char	**new_env;
	int		env_size;
	int		i;

	env_size = 0;
	i = 0;
	while (env[env_size])
		env_size++;
	new_env = (char **)rad_malloc((env_size + 1) * sizeof(char *), 0, ENV);
	if (!new_env)
		return (env);
	while (env[i])
		ft_strdup(env[i++]);
	new_env[i] = NULL;
	return (new_env);
}
