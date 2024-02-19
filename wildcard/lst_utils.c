/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:08:54 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/19 19:14:20 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_list	*lst_make_node(void *data)
{
	t_list	*node;

	node = rad_malloc(sizeof(t_list), 0, COMMAND);
	if (!node)
		return (ft_exit(NULL), NULL);
	node->prev = NULL;
	node->next = NULL;
	node->data = data;
	return (node);
}

void	lst_add_node(t_list **lst, void *data)
{
	t_list	*new;
	t_list	*tmp;

	new = lst_make_node(data);
	if (!new)
		return ;
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