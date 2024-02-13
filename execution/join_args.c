/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 11:32:10 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/13 14:23:07 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <sys/_types/_null.h>

char *argextraction(t_cmd *token, t_env *env)
{
	if (token->cmd && (token->cmd[0] == '"' || token->cmd[0] == '\''))
		return quotes_toexpression(token->cmd, env);
	else if (token->cmd && token->cmd[0] == '$' && token->next && token->next->spaceafter == 0)
		return  ft_strdup(expand(env, &token->cmd[1]));
	else
		return ft_strdup(token->cmd);
}

char **var_toarray(char *token, t_env *env)
{
	char	*key;
	char	**res;

	key = ft_strdup(expand(env, &token[1]));
	if(!key)
		return NULL;
	res = ft_split(key, 32);
	return res;
}

int count_var_args(char *token, t_env *env)
{
	char	*key;
	char	**res;
	int		i;

	key = ft_strdup(expand(env, &token[1]));
	if(!key)
		return 1;
	res = ft_split(key, 32);
	i = 0;
	while(res[i])
		i++;
	free(key);
	ft_free_array(res);
	if(i != 0)
		return i;
	else
	 	return 0;
}

int args_size(t_cmd *temp, t_env *env)
{
	int i = 0;

	while(temp && temp->cmd)
	{
		if(temp->cmd[0] == '$')
			i += count_var_args(temp->cmd, env);
		else
			i++;
		temp = temp->next;
	}
	return i;
}

char **join_args1(t_cmd *root, t_env *env)
{
	char **args;
	t_cmd *temp;
	char **tmp;
	int i;
	int j = 0;
	int firstit = 0;
	int flag = 0;

	i = -1;
	temp = root;
	if(!temp)
		return NULL;
	args = malloc((args_size(temp, env) + 1) * sizeof(char *));
	if(!args)
		return NULL;
	temp = root;
	temp->spaceafter = 1;
	while(temp && temp->cmd)
	{
		if(temp->cmd[0] == '>' || temp->cmd[0] =='<')
		{
			while(temp && (temp->cmd[0] == '>' || temp->cmd[0] =='<'))
				temp = temp->next->next;
		}
		if(temp && temp->spaceafter == 1 && flag == 0)
		{
			i++;
			args[i] = NULL;
			firstit = 0;
		}
		if (temp && firstit == 0)
		{
			if(temp->cmd[0] != '$')
				args[i] = argextraction(temp, env);
			else
			{
				tmp = var_toarray(temp->cmd, env);
				if(tmp)
				{
					j = 0;
					while(tmp[j])
					{
						if(j == 0)
							args[i] = ft_strdup(tmp[j]);
						else
							args[i] = ft_strjoin(args[i], ft_strdup(tmp[j]));
						j++;
						if(tmp[j])
						{
							i++;
							args[i] = NULL;	
						}
					}
				}
				else if(temp->cmd[0] == '$' && temp->cmd[1] == '\0'){
					args[i] = argextraction(temp, env);
				}
			}
			firstit = 1;
		}
		else if(temp)
		{
			if(temp->cmd[0] != '$')
				args[i] = ft_strjoin(args[i], argextraction(temp, env));
			else
			{
				tmp = var_toarray(temp->cmd, env);
				if(tmp)
				{
					char *test = ft_strdup(expand(env, &temp->cmd[1]));
					if(test && test[0] == 32)
					{
						i++;
						args[i] = NULL;
					}
					j = 0;
					while(tmp[j])
					{
						if(j == 0)
							args[i] = ft_strjoin(args[i], ft_strdup(tmp[j]));
						else 
							args[i] = ft_strdup(tmp[j]);
						j++;
						if(tmp[j])
						{
							i++;
							args[i] = NULL;
						}
					}
				}
				else if(temp->cmd[0] == '$' && temp->cmd[1] == '\0')
				{
					if(args[i] == NULL)
						args[i] = argextraction(temp, env);
					else
					 	args[i] = ft_strjoin(args[i], argextraction(temp, env));

				}
			}
		}
		if(temp)
			temp = temp->next;
		if(args[i] == NULL)
			flag = 1;
		else
		 	flag = 0;
	}
	i++;
	args[i] = NULL;
	return (args);
}
