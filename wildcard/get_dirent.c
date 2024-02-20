/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dirent.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:06:36 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/20 23:33:57 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*get_dirent(void)
{
	DIR				*dir;
	struct dirent	*dp;
	t_list			*lst;

	lst = NULL;
	dir = opendir(".");
	if (!dir)
	{
		wrerror("Turboshell: ");
		perror("");
		exitstatus(1, 1);
		return (NULL);
	}
	dp = readdir(dir);
	while (dp)
	{
		lst_add_node(&lst, (void *)ft_strdup(dp->d_name));
		dp = readdir(dir);
	}
	lst = sort_list(lst, ft_strcmp);
	closedir(dir);
	return (lst);
}
