/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 22:17:48 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/18 16:36:31 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_full_n(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == 'n')
		i++;
	if (!str[i] || str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		return (1);
	return (0);
}

void	print_tilde(t_env *env)
{
	if (!get_value_env(env, "HOME") || get_value_env(env, "HOME")[0] == '\0')
	{
		ft_putstr("/home/");
		ft_putstr(get_value_env(env, "USER"));
	}
	else
		ft_putstr(get_value_env(env, "HOME"));
}

void	print_args(char **args, int j, t_env *env, int flag)
{
	while (args[j])
	{
		if (!ft_strcmp(args[j], "~"))
			print_tilde(env);
		else
			write(1, args[j], ft_strlen(args[j]));
		if (args[j + 1])
			write(1, " ", 1);
		j++;
	}
	if (flag == 1)
		write(1, "\n", 1);
}

int	ft_echo(char **args, t_env **env)
{
	int	flag;
	int	j;

	flag = 1;
	j = 1;
	if (!args)
		return (0);
	while (args[j] && args[j][0] == '-')
	{
		if (!is_full_n(&args[j][1]))
			break ;
		else
			flag = 0;
		j++;
	}
	if (flag && j > 1)
		j--;
	print_args(args, j, *env, flag);
	exitstatus(0, 1);
	return (0);
}
