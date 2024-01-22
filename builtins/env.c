/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 15:34:02 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/01/22 11:56:47 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	line_has_value(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '=')
		i++;
	if (line[i] == '=')
		return (1);
	return (0);
}

void	print_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (line_has_value(env[i]))
			printf("%s\n", env[i]);
		i++;
	}
}
