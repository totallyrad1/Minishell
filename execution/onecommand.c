/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   onecommand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 10:15:51 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/15 18:14:24 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>
#include <sys/fcntl.h>
#include <unistd.h>

int	exec_builtin(char **args, t_env **envp)
{
	if (!ft_strcmp(args[0], "cd"))
		return (ft_cd(args, envp));
	if (!ft_strcmp(args[0], "echo"))
		return (ft_echo(args, envp));
	if (!ft_strcmp(args[0], "export"))
		return (ft_export(args, envp));
	if (!ft_strcmp(args[0], "env"))
	{
		print_env(*envp);
		return (0);
	}
	if (!ft_strcmp(args[0], "pwd"))
	{
		get_pwd(*envp);
		return (0);
	}
	if (!ft_strcmp(args[0], "unset"))
		return (unset(args, envp));
	if (!ft_strcmp(args[0], "exit"))
		return (ft_exit(args, *envp));
	return (0);
}

t_cmd	*get_command_start(t_cmd *node)
{
	t_cmd	*curr;

	curr = node;
	if (curr->cmd[0] != '<' && curr->cmd[0] != '>')
		return (curr);
	else
	{
		while (curr)
		{
			if (curr->cmd[0] != '<' && curr->cmd[0] != '>'
				&& curr->next && curr->next->cmd[0] != '<'
				&& curr->next->cmd[0] != '>')
			{
				curr = curr->next;
				return (curr);
			}
			curr = curr->next;
		}
	}
	return (curr);
}

int	builtinexec(char **args, t_env **env, int infile, int outfile)
{
	int	status;
	int	originalout;
	int	originlin;

	originalout = dup(STDOUT_FILENO);
	originlin = dup(STDIN_FILENO);
	changeinfile(infile);
	changeoutfile(outfile);
	status = exec_builtin(args, env);
	if (infile != 0)
		dup2(originlin, STDIN_FILENO);
	if (outfile != 1)
		dup2(originalout, STDOUT_FILENO);
	return (status);
}

int	andorexecution(t_tree *root, t_env *env)
{
	if (root->tree_type == AND)
		return (andorexecution(root->left, env)
			|| andorexecution(root->right, env));
	else if (root->tree_type == OR)
		return (andorexecution(root->left, env)
			&& andorexecution(root->right, env));
	else if (root->tree_type == PIPE)
		return (improvedpipeexecution(root, env));
	else
		return (one_command_execution(root, env));
	return (127);
}
