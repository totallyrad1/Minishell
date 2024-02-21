/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:13:58 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/21 18:38:23 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exitstatus(int newstatus, int flag)
{
	static int	status;

	if (flag == 1)
		status = newstatus;
	return (status);
}

int	hasspaceafter(char *str, int i)
{
	if (i == -1)
		return (0);
	if (ft_isspace(str[i]) == 1)
		return (1);
	return (0);
}

void	new_nodforquotes(t_token **cmd, t_vars *vars, char save)
{
	if (save == '"')
		ft_newnode(cmd, ft_substr(vars->cmd,
				vars->tmp, vars->i - vars->tmp),
			hasspaceafter(vars->cmd, vars->tmp - 1));
	else
		ft_newnode(cmd, ft_substr(vars->cmd,
				vars->tmp, vars->i - vars->tmp),
			hasspaceafter(vars->cmd, vars->tmp - 1));
}

char	*expand(t_env *env, char *key)
{
	if (key[0] == '?' && !key[1])
		return (ft_itoa(exitstatus(0, 0)));
	while (env)
	{
		if (!ft_strcmp(key, env->key))
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (NULL);
}

void	new_node_heredoc(t_token **cmd, t_jnhargs **vars)
{
	t_token	*new;
	t_token	*curr;

	new = rad_malloc(sizeof(t_token), 0, COMMAND);
	curr = *cmd;
	new->cmd = (*vars)->buffer;
	new->spaceafter = (*vars)->spaceafter;
	new->for_heredoc = (*vars)->forheredoc;
	new->visited = 0;
	new->next = NULL;
	if ((*vars)->flag == 1)
	{
		new->prev = NULL;
		*cmd = new;
		(*vars)->flag = 0;
	}
	else
	{
		while (curr->next)
			curr = curr->next;
		new->prev = curr;
		curr->next = new;
	}
}
