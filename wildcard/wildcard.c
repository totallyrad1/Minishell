/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:13:56 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/20 23:12:18 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_len_matching(char *str, t_list *dirent)
{
	int	count;
	
	count = 0;
	while (dirent)
	{
		if (is_match((char *)dirent->data, str))
		{
			dirent->is_matching = 1;
			count++;
		}
		dirent = dirent->next;
	}
	return (count);
}

void	join_dirent(t_list *dirent)
{
	while (dirent)
	{
		dirent->data = (void *)ft_strjoin("./", (char *)dirent->data);
		dirent = dirent->next;
	}
}

t_list	*remove_hidden(t_list *dirent)
{
	t_list	*new_list;
	t_list	*head;

	new_list = NULL;
	head = dirent;
	while (dirent)
	{
		if (((char *)dirent->data)[0] != '.')
			lst_add_node(&new_list, ft_strdup((char *)dirent->data));
		dirent = dirent->next;
	}
	free_list(&head);
	return (new_list);
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
	if (str[0] == '.' && str[1] == '/')
	{
		dirent = remove_hidden(dirent);
		join_dirent(dirent);
	}
	else if (str[0] != '.')
		dirent = remove_hidden(dirent);
	len_ret = count_len_matching(str, dirent);
	if (!ft_strchr(str, '*') || !args->expandwildcard || len_ret == 0)
	{
		ret = rad_malloc(sizeof(char *) * 2, 0, COMMAND);
		if (!ret)
			return (ft_exit(NULL), NULL);
		ret[0] = ft_strdup(args->cmd);
		ret[1] = NULL;
		return (ret);
	}
	ret = rad_malloc(sizeof(char *) * (len_ret + 1), 0, COMMAND);
	if (!ret)
		return (ft_exit(NULL), NULL);
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

char	**args_to_arr(t_cmd *args)
{
	int		len;
	t_cmd	*head;
	char	**ret;

	len = 0;
	head = args;
	while (args)
	{
		len++;
		args = args->next;
	}
	ret = rad_malloc(sizeof(char *) * (len + 1), 0, COMMAND);
	if (!ret)
		return (ft_exit(NULL), NULL);
	args = head;
	len = 0;
	while (args)
	{
		ret[len++] = ft_strdup(args->cmd);
		args = args->next;
	}
	ret[len] = NULL;
	return (ret);
}

char	**get_all_wildcards(t_cmd *args)
{
	t_list	*lst;
	char	**ret;
	int		i;
	int		j;

	if (!ft_strcmp(args->cmd, "export"))
		return (args_to_arr(args));
	lst = NULL;
	while (args)
	{
		lst_add_node(&lst, (void *)wildcard(args));
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
