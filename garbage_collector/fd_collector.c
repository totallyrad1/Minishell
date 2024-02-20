/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_collector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 20:04:53 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/20 20:28:10 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <unistd.h>

static void new_fd_list_node(t_fd_list **list, int *it, int fd)
{
	t_fd_list	*curr;
	t_fd_list	*new;

	new = malloc(sizeof(t_fd_list));
	if (!new)
		ft_exit(NULL);
	new->fd = fd;
	new->next = NULL;
	if(*it == 0)
	{
		*list = new;
		*it = 1;
	}
	else 
	{
		curr = *list;
		while(curr->next)
			curr = curr->next;
		curr->next = new;
	}
}

static void closefds(t_fd_list **fd_list)
{
	t_fd_list *curr;
	t_fd_list *tofree;
	
	curr = *fd_list;
	while(curr)
	{
		tofree = curr;
		curr = curr->next;
		if (tofree->fd > 2)
			close(tofree->fd);
		free(tofree);
	}
	*fd_list = NULL;
}

void addfd(int fd, int flag)
{
	static int			firstit;
	static t_fd_list	*fd_list;

	if (flag == 1)
		new_fd_list_node(&fd_list, &firstit, fd);
	else if (flag == 0)
	{
		closefds(&fd_list);
		firstit = 0;
	}
}