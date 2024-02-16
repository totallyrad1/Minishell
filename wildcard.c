/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:15:06 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/16 17:17:03 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

static t_list	*lst_make_node(void *data)
{
	t_list	*node;

	node = rad_malloc(sizeof(t_list), 0, 0);
	if (!node)
		return (NULL);
	node->data = data;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

static void	lst_add_node(t_list **lst, void *data)
{
	t_list	*new;
	t_list	*tmp;

	new = lst_make_node(data);
	if (!new)
		return ;
	if (!lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		(*lst)->size = 1;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	(*lst)->size++;
}

static char	*get_before_wildcard(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '*' && str[i] != '\n')
		i++;
	return (ft_strdup_len(str, i));
}

static char	*get_after_wildcard(char *str)
{
	if (!str)
		return (NULL);
	while (*str && *str != '*' && *str != '\n')
		str++;
	if (*str == '*')
		str++;
	return (ft_strdup(str));
}

static char	**get_wildcard(t_list *lst, char *before, char *after)
{
	char	**ret;
	int		count;
	t_list	*head;
	int		after_check;
	int		before_check;

	count = 0;
	head = lst;
	while (lst)
	{
		after_check = 0;
		before_check = 0;
		if (!*before || !before)
			before_check = 1;
		else if (!ft_strncmp(before, (char *)lst->data, ft_strlen(before)))
			before_check = 1;
		if (!*after)
			after_check = 1;
		else if (!ft_strncmp_rev(after, (char *)lst->data, ft_strlen(after)))
			after_check = 1;
		if (before_check && after_check && *(char *)lst->data != '.')
			count++;

		lst = lst->next;
	}
	ret = rad_malloc(sizeof(char *) * (count + 1), 0, 0);
	if (!ret)
		return (NULL);
	lst = head;
	count = 0;
	while (lst)
	{
		after_check = 0;
		before_check = 0;
		if (!*before)
			before_check = 1;
		else if (!ft_strncmp(before, (char *)lst->data, ft_strlen(before)))
			before_check = 1;
		if (!*after)
			after_check = 1;
		else if (!ft_strncmp_rev(after, (char *)lst->data, ft_strlen(after)))
			after_check = 1;
		if (before_check && after_check && *(char *)lst->data != '.')
			ret[count++] = ft_strdup((char *)lst->data);
		lst = lst->next;
	}
	ret[count] = NULL;
	return (ret);
}

static t_list	*get_dirent()
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

char	**wildcard(t_cmd *args)
{
	char	*before_wildcard;
	char	*after_wildcard;
	char	**ret;
	t_list	*lst;
	char	*str;

	str = args->cmd;
	if (!ft_strchr(str, '*') || !args->expand)
	{
		ret = rad_malloc(sizeof(char *) * 2, 0, 0);
		ret[0] = ft_strdup(str);
		ret[1] = NULL;
		return (ret);
	}
	lst = get_dirent();
	before_wildcard = get_before_wildcard(str);
	after_wildcard = get_after_wildcard(str);
	ret = get_wildcard(lst, before_wildcard, after_wildcard);
	return (ret);
}

static int	array_len(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

char	**get_all_wildcards(t_cmd *args)
{
	t_list	*lst;
	int		i;
	char	**ret;
	t_list	*head;
	int		count;

	i = 0;
	lst = NULL;
	while (args)
	{
		lst_add_node(&lst, (void *)wildcard(args));
		args = args->next;
	}
	head = lst;
	count = 0;
	while (lst)
	{
		count += array_len((char **)lst->data);
		lst = lst->next;
	}
	lst = head;
	ret = rad_malloc(sizeof(char *) * (count + 1), 0, 0);
	i = 0;
	while (i < count)
	{
		int	j = 0;
		while (((char **)lst->data)[j])
			ret[i++] = ft_strdup(((char **)lst->data)[j++]);
		lst = lst->next;
	}
	ret[i] = NULL;
	return (ret);
}
