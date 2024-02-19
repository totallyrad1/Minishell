/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:13:56 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/19 19:15:16 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_full_asterisk(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] == '*')
		i++;
	if (str && !str[i])
		return (1);
	return (0);
}

char	**wildcard(t_cmd *args, t_list *dir_entries)
{
	char	*str;
	char	**ret;
	int		i;
	t_list	*dirent;

	if (!dir_entries)
		dirent = get_dirent();
	else
		dirent = dir_entries;
	str = args->cmd;
	if (!is_full_asterisk(str) || !args->expandwildcard)
	{
		ret = rad_malloc(sizeof(char *) * 2, 0, COMMAND);
		if (!ret)
			return (ft_exit(NULL), NULL);
		ret[0] = ft_strdup(args->cmd);
		ret[1] = NULL;
		return (ret);
	}
	ret = rad_malloc(sizeof(char *) * (dirent->size + 1), 0, COMMAND);
	if (!ret)
		return (ft_exit(NULL), NULL);
	i = 0;
	while (dirent)
	{
		ret[i++] = ft_strdup((char *)dirent->data);
		dirent = dirent->next;
	}
	ret[i] = NULL;
	return (ret);
}

char	**get_all_wildcards(t_cmd *args)
{
	t_list	*dirent;
	t_list	*lst;
	char	**ret;
	int		i;
	int		j;

	dirent = get_dirent();
	lst = NULL;
	while (args)
	{
		lst_add_node(&lst, (void *)wildcard(args, dirent));
		args = args->next;
	}
	ret = rad_malloc(sizeof(char *) * (len_arr_list(lst) + 1), 0, COMMAND);
	if (!ret)
		return (ft_exit(NULL), NULL);
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