/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeexecution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:55:56 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/18 12:46:02 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pipe_part1(t_tree *node, t_env *env, t_tree *save)
{
	pid_t	id;

	pipe(node->fd);
	id = fork();
	if (id == -1)
	{
		wrerror("turboshell: fork: Resource temporarily unavailable\n");
		return (127);
	}
	if (id == 0)
	{
		close(save->fd[1]);
		dup2(save->fd[0], STDIN_FILENO);
		close(save->fd[0]);
		close(node->fd[0]);
		dup2(node->fd[1], STDOUT_FILENO);
		close(node->fd[1]);
		if (andorexecution(node->left, env) != 0)
			exit(127);
		exit(0);
	}
	close(save->fd[1]);
	close(save->fd[0]);
	save = node;
	return (improvedpipeexecution1(node->right, env, save));
}

int	pipe_part2(t_tree *node, t_env *env, t_tree *save)
{
	int		status;
	pid_t	id;

	status = 0;
	id = fork();
	if (id == -1)
	{
		wrerror("turboshell: fork: Resource temporarily unavailable\n");
		ft_exit(NULL, env);
	}
	if (id == 0)
	{
		close(save->fd[1]);
		dup2(save->fd[0], STDIN_FILENO);
		close(save->fd[0]);
		if (andorexecution(node, env) != 0)
			exit(127);
		exit(0);
	}
	close(save->fd[1]);
	close(save->fd[0]);
	while (wait(&status) != -1)
		;
	status = exitstatus(WEXITSTATUS(status), 1);
	return (status);
}

int	improvedpipeexecution1(t_tree *node, t_env *env, t_tree *save)
{
	if (node && node->tree_type == PIPE)
		return (pipe_part1(node, env, save));
	else
		return (pipe_part2(node, env, save));
}

int	improvedpipeexecution(t_tree *node, t_env *env)
{
	t_tree	*save;
	pid_t	id;

	if (pipe(node->fd) == -1)
	{
		wrerror("pipe failed\n");
		ft_exit(NULL, env);
	}
	id = fork();
	if (id == -1)
	{
		wrerror("turboshell: fork: Resource temporarily unavailable\n");
		return (127);
	}
	if (id == 0)
	{
		close(node->fd[0]);
		dup2(node->fd[1], STDOUT_FILENO);
		close(node->fd[1]);
		if (andorexecution(node->left, env) != 0)
			exit(127);
		exit(0);
	}
	save = node;
	return (improvedpipeexecution1(node->right, env, save));
}
