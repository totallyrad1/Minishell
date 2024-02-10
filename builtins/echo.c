/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 22:17:48 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/09 14:34:51 by asnaji           ###   ########.fr       */
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
	while(args[j])
	{
		if (!ft_strcmp(args[j], "~"))
		{
			write(1, "/home/", 6);
			write(1, get_value_env(*env, "USERNAME"), ft_strlen(get_value_env(*env, "USERNAME")));
		}
		else
			write(1, args[j], ft_strlen(args[j]));
		if (args[j + 1])
			write(1, " ", 1);
		j++;
	}		
	if (flag == 1)
		write(1, "\n", 1);
	return (0);
}
