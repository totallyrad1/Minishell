/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 15:27:22 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/01/13 17:55:59 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_pwd(char **envp)
{
	int		i;
	char	*line_pwd;

	i = 0;
	while(envp[i])
	{
		if(!ft_strncmp("PWD", envp[i], 3))
			break ;
		i++;
	}
	line_pwd = ft_substr(envp[i], 4, ft_strlen(envp[i] + 4));
	return (line_pwd);
}