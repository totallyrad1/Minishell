/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_args1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:50:42 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/14 11:29:10 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void  firstit1(char **args, int *i, char **tmp)
{
	int	j;

	j = 0;
	while(tmp[j])
	{
		if(j == 0)
			args[*i] = ft_strdup(tmp[j]);
		else
			args[*i] = ft_strjoin(args[*i], ft_strdup(tmp[j]));
		j++;
		if(tmp[j])
		{
			(*i)++;
			args[*i] = NULL;	
		}
	}
}

void ft_firstit(t_cmd *token, int *i, t_env *env, char **args)
{
	char **tmp;

	if(token->cmd[0] != '$')
		args[*i] = argextraction(token, env);
	else
	{
		tmp = var_toarray(token->cmd, env);
		if (tmp)
			firstit1(args, i, tmp);
		else if (token->cmd[0] == '$' && token->cmd[1] == '\0')
			args[*i] = argextraction(token, env);
	}
}

void ft_secondit1(char **args, int *i, char **tmp)
{
	int	j;

	j = 0;
	while(tmp[j])
	{
		if(j == 0)
			args[*i] = ft_strjoin(args[*i], ft_strdup(tmp[j]));
		else 
			args[*i] = ft_strdup(tmp[j]);
		j++;
		if(tmp[j])
		{
			i++;
			args[*i] = NULL;
		}
	}
}

void ft_secondit(t_cmd *token, int *i, t_env *env, char **args)
{
	char **tmp;

	if(token->cmd[0] != '$')
		args[*i] = ft_strjoin(args[*i], argextraction(token, env));
	else
	{
		tmp = var_toarray(token->cmd, env);
		if(tmp)
		{
			if(check_expanded_var(token->cmd, env) == 1)
			{
				(*i)++;
				args[*i] = NULL;
			}
			ft_secondit1(args, i, tmp);
		}
		else if(token->cmd[0] == '$' && token->cmd[1] == '\0')
		{
			if(args[*i] == NULL)
				args[*i] = argextraction(token, env);
			else
			 	args[*i] = ft_strjoin(args[*i], argextraction(token, env));
		}
	}
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
	args = malloc((args_size(temp, env) + 1) * sizeof(char *));
	if(!args)
		return NULL;
	temp->spaceafter = 1;
	while(temp && temp->cmd)
	{
		if(temp->cmd[0] == '>' || temp->cmd[0] =='<')
			while(temp && (temp->cmd[0] == '>' || temp->cmd[0] =='<'))
				temp = temp->next->next;
		if(temp && temp->spaceafter == 1 && flag == 0)
		{
			args[++i] = NULL;
			firstit = 0;
		}
		if (temp && firstit == 0)
		{
			ft_firstit(temp, &i, env, args);
			firstit = 1;
		}
		else if(temp)
			ft_secondit(temp, &i, env, args);
		if(temp)
			temp = temp->next;
		if(args[i] == NULL)
			flag = 1;
		else
		 	flag = 0;
	}
	args[++i] = NULL;
	return (args);
}
