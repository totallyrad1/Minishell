/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_home_dir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:47:11 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/01/13 17:55:56 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_home_dir(char **envp)
{
	int		i;
	char	*line_home;

	i = 0;
	while(envp[i])
	{
		if(!ft_strncmp("HOME", envp[i], 4))
			break ;
		i++;
	}
	line_home = ft_substr(envp[i], 5, ft_strlen(line_home + 5));
	return (line_home);
}
