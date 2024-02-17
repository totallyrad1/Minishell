/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:15:06 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/17 22:37:33 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	malloc_len_arr(t_list *lst, char *before, char *after)
{
	int	after_check;
	int	before_check;
	int	count;

	count = 0;
	while (lst)
	{
		after_check = 0;
		before_check = 0;
		if (!*before || !before)
			before_check = 1;
		else if (!ft_strncmp(before, (char *)lst->data, ft_strlen(before)))
			before_check = 1;
		if (!*after || !after)
			after_check = 1;
		else if (!ft_strncmp_rev(after, (char *)lst->data, ft_strlen(after)))
			after_check = 1;
		if (before_check && after_check && *(char *)lst->data != '.')
			count++;
		lst = lst->next;
	}
	return (count);
}

static void	fill_array(t_list *lst, char *before, char *after, char **ret)
{
	int	after_check;
	int	before_check;
	int	i;

	i = 0;
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
			ret[i++] = ft_strdup((char *)lst->data);
		lst = lst->next;
	}
	ret[i] = NULL;
}

static char	**get_wildcard(t_list *lst, char *before, char *after, char *str)
{
	char	**ret;
	int		count;

	count = malloc_len_arr(lst, before, after);
	if (count == 0)
		return (ret_same(str));
	ret = rad_malloc(sizeof(char *) * (count + 1), 0, COMMAND);
	if (!ret)
		return (NULL);
	count = 0;
	fill_array(lst, before, after, ret);
	return (ret);
}

char	**wildcard(t_cmd *args)
{
	char	*before_wildcard;
	char	*after_wildcard;
	char	**ret;
	t_list	*lst;
	char	*str;

	str = args->cmd;
	if (!ft_strchr(str, '*') || !args->expandwildcard)
	{
		ret = rad_malloc(sizeof(char *) * 2, 0, COMMAND);
		ret[0] = ft_strdup(str);
		ret[1] = NULL;
		return (ret);
	}
	lst = get_dirent();
	before_wildcard = get_before_wildcard(str);
	after_wildcard = get_after_wildcard(str);
	ret = get_wildcard(lst, before_wildcard, after_wildcard, str);
	return (ret);
}

char	**get_all_wildcards(t_cmd *args)
{
	t_list	*lst;
	int		i;
	int		j;
	char	**ret;
	int		count;

	i = 0;
	lst = fill_lst(args);
	count = count_len_list(lst);
	ret = rad_malloc(sizeof(char *) * (count + 1), 0, COMMAND);
	if (!ret)
		return (NULL);
	i = 0;
	while (i < count)
	{
		j = 0;
		while (((char **)lst->data)[j])
			ret[i++] = ft_strdup(((char **)lst->data)[j++]);
		lst = lst->next;
	}
	ret[i] = NULL;
	return (ret);
}
