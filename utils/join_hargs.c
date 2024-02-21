/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_hargs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:33:08 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/21 17:58:22 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*removequotesfromheredocargs(char *str)
{
	int		i;
	char	save;

	i = 0;
	save = str[i++];
	while (str[i] && str[i] != save)
		i++;
	return (ft_substr(str, 1, i - 1));
}

void	jnhargsstart(t_jnhargs **vars, t_token **curr, t_token **newlst)
{
	(*vars)->spaceafter = (*curr)->spaceafter;
	(*vars)->buffer = ft_strdup((*curr)->cmd);
	new_node_heredoc(newlst, vars);
	(*vars)->buffer = NULL;
	(*curr) = (*curr)->next;
	(*vars)->spaceafter = (*curr)->spaceafter;
	(*curr)->spaceafter = 0;
	(*vars)->forheredoc = 0;
}

void	elseforjnhargs(t_jnhargs **vars, t_token **curr, t_token **newlst)
{
	(*vars)->spaceafter = (*curr)->spaceafter;
	(*vars)->buffer = ft_strdup((*curr)->cmd);
	new_node_heredoc(newlst, vars);
	*curr = (*curr)->next;
}

void	jnhargs_while(t_token **curr, t_jnhargs **vars)
{
	if ((*curr)->cmd[0] == '\'' || (*curr)->cmd[0] == '"')
	{
		(*vars)->forheredoc = 1;
		(*vars)->buffer = ft_strjoin((*vars)->buffer,
				removequotesfromheredocargs((*curr)->cmd));
	}
	else if ((*curr)->cmd[0] == '$' && !(*curr)->cmd[1] && (*curr)->next)
	{
		if ((*curr)->next && (*curr)->next->cmd[0] != '"'
			&& (*curr)->next->cmd[0] != '\'')
			(*vars)->buffer = ft_strjoin((*vars)->buffer, (*curr)->cmd);
	}
	else
		(*vars)->buffer = ft_strjoin((*vars)->buffer, (*curr)->cmd);
	(*curr) = (*curr)->next;
}

t_token	*join_heredocargs(t_token *curr)
{
	t_jnhargs	*vars;
	t_token		*new;

	vars = rad_malloc(sizeof(t_jnhargs), 0, COMMAND);
	vars->flag = 1;
	vars->forheredoc = 0;
	while (curr)
	{
		if (curr->cmd[0] == '<' && curr->cmd[1] == '<'
			&& curr->next && islimiter1(curr->next->cmd[0]) == 0)
		{
			jnhargsstart(&vars, &curr, &new);
			while (curr && curr->spaceafter != 1
				&& islimiter1(curr->cmd[0]) == 0
				&& curr->cmd[0] != ')' && curr->cmd[0] != '(')
				jnhargs_while(&curr, &vars);
			new_node_heredoc(&new, &vars);
		}
		else
			elseforjnhargs(&vars, &curr, &new);
		vars->buffer = NULL;
	}
	return (new);
}
