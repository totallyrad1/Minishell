/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_parsing2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 14:21:20 by asnaji            #+#    #+#             */
/*   Updated: 2024/01/31 21:55:53 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token *join_args_ifspace(t_token *cmd)
{
	t_token *new_cmd;
	t_token *curr;
	char *wordsjoined;
	int i;
	int tnp;
	int state;

	if(!cmd)
		return NULL;
	curr = cmd;
	new_cmd = init_token();
	i = 0;
	tnp = 1;
	wordsjoined = NULL;
	while(curr)
	{
		wordsjoined = NULL;
		i = 0;
		if(curr->spaceafter == 0 && curr->next && curr->next->type == TOKEN_EXPR && curr->type == TOKEN_EXPR)
		{
			while(curr && curr->next && curr->next->type == TOKEN_EXPR && curr->spaceafter == 0)
			{
				if(i == 0)
				{
					wordsjoined = ft_strjoin(curr->cmd, curr->next->cmd);
					i = 1;
				}
				else
					wordsjoined = ft_strjoin(wordsjoined, curr->next->cmd);
				curr = curr->next;	
			}
			if(tnp == 1)
			{
				new_cmd->cmd = wordsjoined;
				new_cmd->state = GENERAL;
				tnp = 0;
			}
			else
				ft_newnode(&new_cmd, wordsjoined, 0, 0);
		}
		else
		{
			if(tnp == 1)
			{
				new_cmd->cmd = ft_strdup(curr->cmd);
				new_cmd->state = GENERAL;
				tnp = 0;
			}
			else
				ft_newnode(&new_cmd, ft_strdup(curr->cmd), 0, 0);
		}
		curr = curr->next;
	}
	return new_cmd;
}
