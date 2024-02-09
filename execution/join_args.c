/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 11:32:10 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/09 14:37:39 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <sys/_types/_null.h>

char *argextraction(t_cmd *token, t_env *env)
{
	if (token->cmd && (token->cmd[0] == '"' || token->cmd[0] == '\''))
		return quotes_toexpression(token->cmd, env);
	else if (token->cmd && token->cmd[0] == '$')
		return  ft_strdup(expand(env, &token->cmd[1]));
	else
		return ft_strdup(token->cmd);
}

int args_size(t_cmd *temp)
{
	int i = 0;

	while(temp && temp->cmd && temp->cmd[0] != '<' && temp->cmd[0] != '>')
	{	
		i++;
		temp = temp->next;
	}
	return i;
}

char **join_args1(t_tree *root , t_env *env)
{
	char **args;
	t_cmd *temp;
	// char *tmp;
	int i;
	int firstit = 0;

	i = -1;
	temp = root->next;
	args = malloc((args_size(temp) + 1) * sizeof(char *));
	if(!args)
		return NULL;
	temp = root->next;
	temp->spaceafter = 1;
	while(temp && temp->cmd && temp->cmd[0] != '<' && temp->cmd[0] != '>')
	{
		if(temp->spaceafter == 1)
		{
			i++;
			firstit = 0;
		}
		if (firstit == 0)
		{
			args[i] = argextraction(temp, env);
			firstit = 1;
		}
		else 
		{
			args[i] = ft_strjoin(args[i], argextraction(temp, env));
		}
		temp = temp->next;
		if(args[i] == NULL && firstit == 0)
			i--;
	}
	i++;
	args[i] = NULL;
	return (args);
}
