/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:13:56 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/22 17:10:46 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	check_dots(char *str, t_list **dirent)
{
	if (str && str[0] == '.' && str[1] == '/')
	{
		*dirent = remove_hidden(*dirent);
		join_dirent(*dirent);
	}
	else if (str && str[0] != '.')
		*dirent = remove_hidden(*dirent);
}

static char	**ret_same(char *str)
{
	char	**ret;

	ret = rad_malloc(sizeof(char *) * 2, 0, COMMAND);
	ret[0] = ft_strdup(str);
	ret[1] = NULL;
	return (ret);
}

char	**wildcard(t_cmd *args)
{
	char	*str;
	char	**ret;
	int		i;
	t_list	*dirent;
	int		len_ret;

	dirent = get_dirent();
	str = args->cmd;
	check_dots(str, &dirent);
	len_ret = count_len_matching(str, dirent);
	if (!ft_strchr(str, '*') || !args->expandwildcard || len_ret == 0)
		return (ret_same(str));
	ret = rad_malloc(sizeof(char *) * (len_ret + 1), 0, COMMAND);
	i = 0;
	while (dirent)
	{
		if (dirent->is_matching)
			ret[i++] = ft_strdup((char *)dirent->data);
		dirent = dirent->next;
	}
	ret[i] = NULL;
	return (ret);
}

static char	**get_final_arr(t_list *lst)
{
	int		i;
	int		j;
	char	**ret;

	ret = rad_malloc(sizeof(char *) * (len_arr_list(lst) + 1), 0, COMMAND);
	i = 0;
	while (lst)
	{
		j = 0;
		while (((char **)lst->data)[j])
			ret[i++] = ft_strdup(((char **)lst->data)[j++]);
		lst = lst->next;
	}
	ret[i] = NULL;
	return (ret);
}

char	**get_all_wildcards(t_cmd *args)
{
	t_list	*lst;

	if (!ft_strcmp(args->cmd, "export"))
		return (args_to_arr(args));
	lst = NULL;
	while (args)
	{
		lst_add_node(&lst, (void *)wildcard(args));
		args = args->next;
	}
	return (get_final_arr(lst));
}
