/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_args4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 01:08:20 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/18 01:19:33 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	make_args_node1(t_cmd **args, t_jn_args **vars)
{
	t_cmd	*new;
	t_cmd	*curr;

	new = rad_malloc(sizeof(t_cmd), 0, COMMAND);
	if (!new)
		return ;
	new->spaceafter = (*vars)->spaceafter;
	new->cmd = (*vars)->buffer;
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

void	joined_p1(t_cmd **args, t_jn_args **vars)
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

void	joined_p2(t_cmd **args, t_jn_args **vars)
{
	if ((*args)->cmd && ft_strchr((*args)->cmd, '*'))
		(*vars)->expand = (*args)->expandwildcard;
	if ((*args)->cmd)
		(*vars)->buffer = ft_strjoin((*vars)->buffer, (*args)->cmd);
	*args = (*args)->next;
}

t_cmd	*joined_args(t_cmd *args, t_env *env)
{
	t_jn_args	*vars;
	t_cmd		*new;

	vars = rad_malloc(sizeof(t_jn_args), 0, COMMAND);
	if (!vars)
		ft_exit(NULL, env);
	vars->flag = 1;
	vars->expand = 0;
	vars->buffer = NULL;
	while (args)
	{
		skip_redirections(&args);
		vars->expand = 0;
		if (args)
			vars->spaceafter = args->spaceafter;
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
