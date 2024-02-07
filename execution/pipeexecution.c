/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeexecution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:55:56 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/07 08:32:48 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int improvedpipeexecution1(t_tree *node, t_env *env, t_tree *save)
{
	pid_t id;
	int status = 0;

	if(node && node->tree_type == PIPE)
	{
		pipe(node->fd);
		id = fork();
		if(id == 0)
		{
			close(save->fd[1]);
			dup2(save->fd[0],STDIN_FILENO);
			close(save->fd[0]);
			close(node->fd[0]);
			dup2(node->fd[1], STDOUT_FILENO);
			close(node->fd[1]);
			if(andorexecution(node->left, env) != 0)
				exit(127);
			exit(0);
		}
		close(save->fd[1]);
		close(save->fd[0]);
		wait(&status);
		exitstatus(WEXITSTATUS(status), 1);
		if(status != 0)
			return improvedpipeexecution1(node->right, env, save);
		save = node;
		return improvedpipeexecution1(node->right, env, save);
	}
	else {
		id = fork();
		if(id == 0)
		{
			close(save->fd[1]);
			dup2(save->fd[0],STDIN_FILENO);
			close(save->fd[0]);
			if(andorexecution(node, env) != 0)
				exit(127);
			exit(0);
		}
		close(save->fd[1]);
		close(save->fd[0]);
		wait(&status);
		exitstatus(WEXITSTATUS(status), 1);
		if(status != 0)
			return 127;
	}
	return status;
}

int improvedpipeexecution(t_tree *node, t_env *env)
{
	t_tree *save;
	pid_t id;
	int status = 0;

	pipe(node->fd);
	id = fork();
	if(id == 0)
	{
		close(node->fd[0]);
		dup2(node->fd[1], STDOUT_FILENO);
		close(node->fd[1]);
		if(andorexecution(node->left, env) != 0)
			exit(127);
		exit(0);
	}
	wait(&status);
	exitstatus(WEXITSTATUS(status), 1);	
	save = node;
	improvedpipeexecution1(node->right, env, save);
	return (status);
}
