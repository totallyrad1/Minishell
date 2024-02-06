/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 22:17:48 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/06 17:07:19 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(char **args)
{
	int	flag;
	int	i;

	flag = 1;
	i = 1;
	if (!args)
		return (0);
	if(args[1][0] == '-')
	{
		while (args[1][i])
		{
			if (args[1][i++] != 'n')
				flag = 0;
		}
	}
	i = flag + 1;
	while(args[i])
	{
		write(1, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}		
	if (flag == 0)
		write(1, "\n", 1);
	return (0);
}
