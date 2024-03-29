/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_args4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 01:08:20 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/21 21:13:52 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	make_args_node1(t_cmd **args, t_jn_args **vars)
{
	t_cmd	*new;
	t_cmd	*curr;

	new = rad_malloc(sizeof(t_cmd), 0, COMMAND);
	new->spaceafter = (*vars)->spaceafter;
	new->cmd = (*vars)->buffer;
	new->word = (*vars)->word;
	new->expandwildcard = (*vars)->expand;
	new->next = NULL;
	if ((*vars)->flag == 1)
	{
		*args = new;
		(*vars)->flag = 0;
	}
	else
	{
		curr = *args;
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
}

static void	joined_p1(t_cmd **args, t_jn_args **vars)
{
	(*args)->spaceafter = 0;
	while (*args && (*args)->spaceafter != 1)
	{
		if ((*args)->cmd && isredirection((*args)->cmd[0]) == 1)
			break ;
		if ((*args)->cmd && ft_strchr((*args)->cmd, '*'))
			(*vars)->expand = (*args)->expandwildcard;
		if ((*args)->cmd)
			(*vars)->buffer = ft_strjoin((*vars)->buffer, (*args)->cmd);
		*args = (*args)->next;
	}
}

static void	joined_p2(t_cmd **args, t_jn_args **vars)
{
	if ((*args)->cmd && ft_strchr((*args)->cmd, '*'))
		(*vars)->expand = (*args)->expandwildcard;
	if ((*args)->cmd)
		(*vars)->buffer = ft_strjoin((*vars)->buffer, (*args)->cmd);
	*args = (*args)->next;
}

static void	set_word_space(t_cmd *args, t_jn_args **vars)
{
	if (args)
	{
		(*vars)->word = args->word;
		(*vars)->spaceafter = args->spaceafter;
	}
}

t_cmd	*joined_args(t_cmd *args)
{
	t_jn_args	*vars;
	t_cmd		*new;

	vars = rad_malloc(sizeof(t_jn_args), 0, COMMAND);
	vars->flag = 1;
	vars->expand = 0;
	vars->buffer = NULL;
	while (args)
	{
		skip_redirections(&args);
		vars->expand = 0;
		set_word_space(args, &vars);
		if (args && args->cmd && isredirection(args->cmd[0]) == 0)
			joined_p1(&args, &vars);
		else if (args && args->cmd)
			joined_p2(&args, &vars);
		else if (args)
			args = args->next;
		make_args_node1(&new, &vars);
		vars->buffer = NULL;
	}
	return (new);
}
