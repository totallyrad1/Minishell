/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 22:17:48 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/21 21:01:55 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_args(char **args, int i, int flag)
{
	while (args[i])
	{
		ft_putstr(args[i]);
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (flag)
		write(1, "\n", 1);
}

int	ft_echo(char **args)
{
	int	flag;
	int	j;
	int	i;

	flag = 1;
	i = 0;
	if (!args)
		return (0);
	while (args[++i] && args[i][0] == '-' && args[i][1] == 'n')
	{
		j = 2;
		flag = 0;
		while (args[i][j] == 'n')
			j++;
		if (args[i][j])
			break ;
	}
	print_args(args, i, flag);
	exitstatus(0, 1);
	return (0);
}
