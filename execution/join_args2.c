/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_args2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 11:26:05 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/17 23:02:44 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	setflag(int *flag, char *str)
{
	if (!str)
		*flag = 1;
	else
		*flag = 0;
}

void	skip_redirections(t_cmd **temp)
{
	if (*temp && (*temp)->cmd && ((*temp)->cmd[0] == '>' || (*temp)->cmd[0] == '<'))
		while (*temp && (*temp)->cmd && ((*temp)->cmd[0] == '>' || (*temp)->cmd[0] == '<'))
			(*temp) = (*temp)->next->next;
}


void make_args_node(t_cmd **args, t_make_args **vars)
{
	t_cmd *new;
	t_cmd *curr;

	new = rad_malloc(sizeof(t_cmd), 0, COMMAND);
	if(!new)
		return;
	new->spaceafter = (*vars)->spaceafter;
	new->cmd = (*vars)->buffer;
	new->expandwildcard = (*vars)->expand;
	new->expandheredoc = (*vars)->heredocexpand;
	new->next = NULL;
	new->heredocfd = (*vars)->heredocfd;
	new->ambiguous = (*vars)->ambiguos;
	if((*vars)->flag == 1)
	{
		*args = new;
		(*vars)->flag = 0;
	}
	else {
		curr = *args;
		while(curr->next)
			curr = curr->next;
		curr->next = new;
	}
}

t_cmd *make_args_lst(t_cmd *cmd, t_env *env)
{
	t_make_args *vars;
	t_cmd	*new;
	char 	**tmp;
	int		j;

	vars = rad_malloc(sizeof(t_make_args), 0, COMMAND);
	if(!vars)
		ft_exit(NULL, env);
	vars->flag = 1;
	vars->buffer = NULL;
	while(cmd)
	{
		if(cmd->cmd && (cmd->cmd[0] == '<' || cmd->cmd[0] == '>'))
		{
			vars->buffer = argextraction(cmd, env);
			vars->expand = 1;
			vars->heredocfd = cmd->heredocfd;
			vars->heredocexpand = cmd->expandheredoc;
			vars->ambiguos = cmd->ambiguous;
			vars->spaceafter = cmd->spaceafter;
			make_args_node(&new, &vars);
			cmd = cmd->next;
			vars->buffer = ft_strdup(cmd->cmd);
			vars->expand = 1;
			vars->heredocfd = cmd->heredocfd;
			vars->heredocexpand = cmd->expandheredoc;
			vars->ambiguos = cmd->ambiguous;
			vars->spaceafter = cmd->spaceafter;
			make_args_node(&new, &vars);
			cmd = cmd->next;
		}
		else if(cmd->cmd && cmd->cmd[0] == '$') 
		{
			tmp = var_toarray(cmd->cmd, env);
			if (tmp)
			{
				j = 0;
				while (tmp[j])
				{
					vars->buffer = ft_strdup(tmp[j]);
					vars->expand = 1;
					vars->heredocfd = cmd->heredocfd;
					vars->heredocexpand = cmd->expandheredoc;
					vars->ambiguos = cmd->ambiguous;
					if(j == 0)
					{
						if(check_expanded_var(cmd->cmd, env) == 1 || cmd->spaceafter == 1)
						{
							vars->spaceafter = 1;
							make_args_node(&new, &vars);
						}
						else
						{
							vars->spaceafter = 0;
							make_args_node(&new, &vars);
						}
						vars->buffer = NULL;
					}
					else{
						vars->spaceafter = 1;
						make_args_node(&new, &vars);
						vars->buffer = NULL;
					}
					j++;
				}
			}
			else
			{
				vars->buffer = argextraction(cmd, env);
				vars->expand = 1;
				vars->heredocfd = cmd->heredocfd;
				vars->heredocexpand = cmd->expandheredoc;
				vars->ambiguos = cmd->ambiguous;
				vars->spaceafter = cmd->spaceafter;
				make_args_node(&new, &vars);
			}
			cmd = cmd->next;
		}
		else if(cmd->cmd)
		{
			vars->buffer = argextraction(cmd, env);
			vars->expand = 1;
			vars->heredocfd = cmd->heredocfd;
			vars->heredocexpand = cmd->expandheredoc;
			vars->ambiguos = cmd->ambiguous;
			vars->spaceafter = cmd->spaceafter;
			make_args_node(&new, &vars);
			cmd = cmd->next;
		}
	}
	return (new);
}
