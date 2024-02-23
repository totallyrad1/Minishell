/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_wildcard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 23:36:34 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/23 15:53:29 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_len_matching(char *str, t_list *dirent)
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
	return (new_list);
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
