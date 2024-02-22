/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeexecution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:55:56 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/22 17:37:50 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	pipe_part1(t_tree *node, t_env *env, t_tree *save)
{
	pid_t	id;

	if (pipe(node->fd) == -1)
		return (wrerror(PIPE_ERROR), ft_exit(NULL), 0);
	id = fork();
	if (id == -1)
		return (wrerror(FORK_ERROR), ft_exit(NULL), 0);
	if (id == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		close(save->fd[1]);
		dup2(save->fd[0], STDIN_FILENO);
		close(save->fd[0]);
		close(node->fd[0]);
		dup2(node->fd[1], STDOUT_FILENO);
		close(node->fd[1]);
		andorexecution(node->left, env);
		exit(exitstatus(0, 0));
	}
	close(save->fd[1]);
	close(save->fd[0]);
	save = node;
	return (improvedpipeexecution1(node->right, env, save));
}

static int	pipe_part2(t_tree *node, t_env *env, t_tree *save)
{
	int		status;
	pid_t	id;

	status = 0;
	id = fork();
	if (id == -1)
		return (wrerror(FORK_ERROR), ft_exit(NULL), 0);
	if (id == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		close(save->fd[1]);
		dup2(save->fd[0], STDIN_FILENO);
		close(save->fd[0]);
		andorexecution(node, env);
		exit(exitstatus(0, 0));
	}
	close(save->fd[1]);
	close(save->fd[0]);
	while (waitpid(-1, &status, 0) != -1)
		;
	setexit(status);
	return (exitstatus(0, 0));
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
		return (wrerror(PIPE_ERROR), ft_exit(NULL), 0);
	id = fork();
	if (id == -1)
		return (wrerror(FORK_ERROR), ft_exit(NULL), 0);
	if (id == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		close(node->fd[0]);
		dup2(node->fd[1], STDOUT_FILENO);
		close(node->fd[1]);
		andorexecution(node->left, env);
		exit(exitstatus(0, 0));
	}
	save = node;
	return (improvedpipeexecution1(node->right, env, save));
}

void	setvars_argsnode(t_margs **vars, t_cmd **newlst, t_cmd **cmd)
{
	(*newlst)->spaceafter = (*vars)->spaceafter;
	(*newlst)->cmd = (*vars)->buffer;
	(*newlst)->word = (*vars)->word;
	(*newlst)->expandwildcard = (*cmd)->expandwildcard;
	(*newlst)->expandheredoc = (*vars)->heredocexpand;
	(*newlst)->next = NULL;
	(*newlst)->heredocfd = (*vars)->heredocfd;
	(*newlst)->ambiguous = (*vars)->ambiguos;
}
