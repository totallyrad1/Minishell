/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 11:32:10 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/13 17:53:08 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <ctype.h>
// #include <sys/_types/_null.h>

char	*argextraction(t_cmd *token, t_env *env)
{
	if (token->cmd && (token->cmd[0] == '"' || token->cmd[0] == '\''))
		return (quotes_toexpression(token->cmd, env));
	else if (token->cmd && token->cmd[0] == '$'
		&& token->next && token->next->spaceafter == 0)
		return (ft_strdup(expand(env, &token->cmd[1])));
	else
		return (ft_strdup(token->cmd));
}

char	**var_toarray(char *token, t_env *env)
{
	char	*key;
	char	**res;

	key = ft_strdup(expand(env, &token[1]));
	if (!key)
		return (NULL);
	res = ft_split(key, 32);
	return (res);
}

int	count_var_args(char *token, t_env *env)
{
	char	*key;
	char	**res;
	int		i;

	key = ft_strdup(expand(env, &token[1]));
	if (!key)
		return (1);
	res = ft_split(key, 32);
	i = 0;
	while (res[i])
		i++;
	free(key);
	ft_free_array(res);
	if (i != 0)
		return (i);
	else
		return (0);
}

int	args_size(t_cmd *temp, t_env *env)
{
	int	i;

	i = 0;
	while (temp && temp->cmd)
	{
		if (temp->cmd[0] == '$')
			i += count_var_args(temp->cmd, env);
		else
			i++;
		temp = temp->next;
	}
	return (i);
}

int	check_expanded_var(char *str, t_env *env)
{
	char	*key;

	key = expand(env, &str[1]);
	if (key && isspace(key[0]) == 1)
		return (free(key), 1);
	else
		return (free(key), 0);
}
