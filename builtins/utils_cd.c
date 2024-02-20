/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 20:51:39 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/20 23:31:23 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_points(char *str)
{
	int		i;
	int		j;

	i = 0;
	while (str[i] && str[i] != '.')
		i++;
	j = i;
	while (str[j] && str[j] == '.')
		j++;
	return (ft_substr(str, i, j - i));
}

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
