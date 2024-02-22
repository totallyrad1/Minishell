/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 17:32:41 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/22 18:13:42 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_arg(char *str)
{
	int		i;
	long	res;
	long	tmp;

	i = 0;
	res = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		tmp = (res * 10) + (str[i] - '0');
		if (res > tmp)
			return (0);
		res = tmp;
		i++;
	}
	if (!str[i])
		return (1);
	return (0);
}

void	exit_no_args(void)
{
	rl_clear_history();
	rad_malloc(0, 1, 0);
	wrerror("exit\n");
	exit(0);
}

static void	exit_failure(void)
{
	rl_clear_history();
	rad_malloc(0, 1, 0);
	wrerror("exit\n");
	exit(1);
}

void	exit_with_value(int value)
{
	rl_clear_history();
	rad_malloc(0, 1, 0);
	wrerror("exit\n");
	exit(value);
}

void	ft_exit(char **args)
{
	int	exit_value;

	if (!args)
		exit_failure();
	if (!args[1])
		exit_no_args();
	if (!check_arg(args[1]))
	{
		wrerror("exit\n");
		wrerror("Turboshell: exit: ");
		wrerror(args[1]);
		wrerror(": numeric argument required\n");
		exit_value = 255;
		exit(exit_value);
	}
	if (args[2])
	{
		wrerror("exit\n");
		wrerror("Turboshell: exit: too many arguments\n");
		exitstatus(1, 1);
		return ;
	}
	exit_value = ft_atoi(args[1]);
	exit_with_value(exit_value);
}
