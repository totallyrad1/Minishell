/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dirent.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 22:28:58 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/18 16:40:50 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*get_dirent(void)
{
	DIR				*dir;
	struct dirent	*dp;
	t_list			*lst;

	dir = opendir(".");
	dp = readdir(dir);
	lst = NULL;
	if (dp)
	{
		lst = lst_make_node((void *)dp->d_name);
		lst->size = 1;
	}
	while (dp)
	{
		dp = readdir(dir);
		if (dp)
			lst_add_node(&lst, (void *)dp->d_name);
	}
	closedir(dir);
	return (lst);
}
