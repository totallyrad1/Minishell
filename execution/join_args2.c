/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_args2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 11:26:05 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/15 17:48:59 by asnaji           ###   ########.fr       */
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
	if ((*temp)->cmd[0] == '>' || (*temp)->cmd[0] == '<')
		while (*temp && ((*temp)->cmd[0] == '>' || (*temp)->cmd[0] == '<'))
			(*temp) = (*temp)->next->next;
}

char	**join_args1(t_cmd *temp, t_env *env)
{
	char	**args;
	int		i;
	int		firstit;	
	int		flag;

	flag = 0;
	firstit = 0;
	i = -1;
	if (!temp)
		return (NULL);
	args = rad_malloc((args_size(temp, env) + 1) * sizeof(char *), 0, COMMAND);
	if (!args)
		return (NULL);
	temp->spaceafter = 1;
	while (temp && temp->cmd)
	{
		skip_redirections(&temp);
		if (temp && temp->spaceafter == 1 && flag == 0)
		{
			args[++i] = NULL;
			firstit = 0;
		}
		if (temp && firstit == 0)
		{
			ft_firstit(temp, &i, env, args);
			firstit = 1;
		}
		else if (temp)
			ft_secondit(temp, &i, env, args);
		if (temp)
			temp = temp->next;
		setflag(&flag, args[i]);
	}
	return (args[++i] = NULL, args);
}
