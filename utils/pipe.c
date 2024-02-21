/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 17:57:36 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/21 17:28:14 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_path_line(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp("PATH", envp[i], 4) == 0)
			return (envp[i]);
		i++;
	}
	return (NULL);
}

char	*get_working_path(char **envp, char *command)
{
	int		i;
	char	*acesscheck;
	char	*line;
	char	*tpl;
	char	**paths;

	i = 0;
	line = get_path_line(envp);
	if (line == NULL)
		return (NULL);
	tpl = ft_strtrim(line, "PATH=");
	paths = ft_split(tpl, ':');
	while (paths[i])
	{
		acesscheck = ft_strjoin(ft_strdup(paths[i]), "/");
		acesscheck = ft_strjoin(acesscheck, command);
		if (access(acesscheck, X_OK) == 0)
			return (acesscheck);
		i++;
	}
	return (NULL);
}
