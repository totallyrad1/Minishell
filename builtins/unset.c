/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 15:27:25 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/17 16:53:12 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_arg(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (0);
	i++;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	unset(char **args, t_env **envp)
{
	int		i;
	int		args_failed;

	i = 1;
	args_failed = 0;
	while (args[i])
	{
		if (!check_arg(args[i]))
		{
			write(2, "unset: `", 8);
			write(2, args[i], ft_strlen(args[i]));
			write(2, "': not a valid identifier\n", 26);
			args_failed++;
		}
		else
		{
			if (ft_strcmp(args[i], "_"))
				del_node_env(envp, args[i]);
		}
		i++;
	}
	if (args_failed)
		exitstatus(1, 1);
	else
		exitstatus(0, 1);
	return (0);
}
