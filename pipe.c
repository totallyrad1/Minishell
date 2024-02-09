/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 17:57:36 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/09 09:36:09 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_path_line(char **envp)
{
	int i;

	i = 0;
	while(envp[i])
	{
		if(ft_strncmp("PATH", envp[i], 4) == 0)
			return (envp[i]);
		i++;
	}
	return (NULL);
}

char *get_working_path(char **envp, char *command)
{
	int i = 0;
	char *line = get_path_line(envp);
	if (line == NULL)
		return NULL;
	char *tpl = ft_strtrim(line, "PATH=");
	char **paths = ft_split(tpl, ':');
	free(tpl);
	char	*acesscheck;
	while(paths[i])
	{
		acesscheck = ft_strjoin(paths[i], "/");
		acesscheck = ft_strjoin(acesscheck, command);
		if(access(acesscheck, X_OK) == 0)
		{
			// ft_free_array(paths);
			return (acesscheck);
		}
		free(acesscheck);
		i++;
	}
	return (NULL);
}
