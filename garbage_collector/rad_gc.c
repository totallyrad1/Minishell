/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rad_gc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 17:33:01 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/23 15:37:32 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	free_type(t_gc **gc, int type)
{
	t_gc	*curr;

	curr = *gc;
	while (curr->next)
		curr = curr->next;
	while (curr)
	{
		if (curr->type == type)
		{
			if (curr->mallocedptr)
				free(curr->mallocedptr);
			curr->mallocedptr = NULL;
		}
		curr = curr->prev;
	}
}

static void	rad_free(t_gc **gc, int type)
{
	t_gc	*last;
	void	*last_malloced_ptr;

	if (!type)
	{
		while (*gc && (*gc)->next)
			*gc = (*gc)->next;
		while ((*gc))
		{
			last = *gc;
			last_malloced_ptr = (*gc)->mallocedptr;
			(*gc) = (*gc)->prev;
			free(last_malloced_ptr);
			free(last);
		}
	}
	else
		free_type(gc, type);
}

static void	addmallocedptr(void *ptr, t_gc **gc, int flag, int type)
{
	t_gc		*new;
	static t_gc	*last;

	if (flag == 0)
	{
		(*gc)->mallocedptr = ptr;
		last = *gc;
	}
	else
	{
		new = malloc(sizeof(t_gc));
		if (!new)
		{
			ft_exit(NULL);
			return ;
		}
		new->mallocedptr = ptr;
		new->next = NULL;
		new->prev = last;
		new->type = type;
		last->next = new;
		last = new;
	}
}

void	*rad_malloc(size_t size, int flag, int type)
{
	void		*ptr;
	static t_gc	*gc;
	static int	first_iter = 0;

	if (flag == 0)
	{
		ptr = malloc(size);
		if (!ptr)
			return (ft_exit(NULL), NULL);
	}
	else if (flag == 1)
		return (rad_free(&gc, type), NULL);
	if (first_iter == 0)
	{
		gc = malloc(sizeof(t_gc));
		if (!gc)
			return (ft_exit(NULL), NULL);
		gc->next = NULL;
		gc->prev = NULL;
		addmallocedptr(ptr, &gc, first_iter, type);
		first_iter = 1;
	}
	else if (first_iter == 1)
		addmallocedptr(ptr, &gc, first_iter, type);
	return (ptr);
}
