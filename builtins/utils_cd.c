/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 20:51:39 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/22 23:49:52 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	treat_special_cases(char **args, t_env **env)
{
	if (args[1] && args[1][0] == '\0')
		return (0);
	if (args[1] && args[2])
	{
		exitstatus(1, 1);
		return (wrerror("Turboshell: cd: too many arguments\n"), 0);
	}
	if (chdir_home(args, env))
		return (0);
	if (chdir_dash(args, env))
		return (0);
	if (dir_not_found(args))
		return (0);
	return (1);
}
