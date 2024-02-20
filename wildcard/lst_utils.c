/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:08:54 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/20 23:01:37 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_list	*lst_make_node(void *data)
{
	t_list	*node;

	node = rad_malloc(sizeof(t_list), 0, COMMAND);
	if (!node)
		return (ft_exit(NULL), NULL);
	node->data = data;
	node->next = NULL;
	node->prev = NULL;
	node->is_matching = 0;
	return (node);
}

void	lst_add_node(t_list **lst, void *data)
{
	t_list	*new;
	t_list	*tmp;

	new = lst_make_node(data);
	if (!*lst)
	{
		*lst = new;
		new->size = 1;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	(*lst)->size++;
}

int	len_arr_list(t_list *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count += array_len((char **)lst->data);
		lst = lst->next;
	}
	return (count);
}

t_list	*sort_list(t_list* lst, int (*cmp)(const char *, const char *))
{
	int swapped;
	t_list *cur;
	char	*tmp;

	swapped = 1;
	cur = lst;
	while (swapped == 1)
	{
		swapped = 0;
		while (cur != 0 && cur->next != 0)
		{
			if (cmp(cur->data, cur->next->data) > 0)
			{
				tmp = (char *)cur->data;
				cur->data = cur->next->data;
				cur->next->data = tmp;
				swapped = 1;
			}
			cur = cur->next;
		}
		cur = lst;
	}
	return (lst);
}

void	free_list(t_list **lst)
{
	t_list	*tmp;

	if (!lst)
		return ;
	if (!*lst)
	{
		free(*lst);
		return ;
	}
	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp->data);
		free(tmp);
	}
}