/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 22:27:59 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/17 22:34:22 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*lst_make_node(void *data)
{
	t_list	*node;

	node = rad_malloc(sizeof(t_list), 0, COMMAND);
	if (!node)
		return (NULL);
	node->data = data;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	lst_add_node(t_list **lst, void *data)
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

int	count_len_list(t_list *lst)
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

t_list	*fill_lst(t_cmd *args)
{
	t_list	*lst;

	lst = NULL;
	while (args)
	{
		lst_add_node(&lst, (void *)wildcard(args));
		args = args->next;
	}
	return (lst);
}
