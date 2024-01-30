/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeexecution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:55:56 by asnaji            #+#    #+#             */
/*   Updated: 2024/01/30 20:36:42 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <unistd.h>

void pipeexecution1(t_tree *node, t_tree *save, t_env *env)
{
	pid_t id;

	if(node->right->tree_type == PIPE)
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
			one_command_execution(node->left, env);
			exit(0);
		}
		close(save->fd[1]);
		close(save->fd[0]);
		wait(NULL);
		save = node;
		pipeexecution1(node->right, save, env);
	}
	if(node->right->tree_type == CMD)
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
			one_command_execution(node->left, env);
			exit(0);
		}
		close(save->fd[1]);
		close(save->fd[0]);
		wait(NULL);
		id = fork();
		if(id == 0)
		{
			close(node->fd[1]);
			dup2(node->fd[0],STDIN_FILENO);
			close(node->fd[0]);
			one_command_execution(node->right, env);
			exit(0);
		}
		close(save->fd[1]);
		close(save->fd[0]);
		close(node->fd[1]);
		close(node->fd[0]);
		wait(NULL);
	}
}

void pipe_execution(t_tree *node, t_env *env)
{
	t_tree *save;
	pid_t id;

	if(node->right->tree_type == PIPE)
	{
		pipe(node->fd);
		id = fork();
		if(id == 0)
		{
			close(node->fd[0]);
			dup2(node->fd[1], STDOUT_FILENO);
			close(node->fd[1]);
			one_command_execution(node->left, env);
			exit(0);
		}
		wait(NULL);
		save = node;
		pipeexecution1(node->right, save, env);
	}
	else {
		pipe(node->fd);
		id = fork();
		if(id == 0)
		{
			close(node->fd[0]);
			dup2(node->fd[1], STDOUT_FILENO);
			close(node->fd[1]);
			one_command_execution(node->left, env);
			exit(0);
		}
		wait(NULL);
		id = fork();
		if(id == 0)
		{
			close(node->fd[1]);
			dup2(node->fd[0],STDIN_FILENO);
			close(node->fd[0]);
			one_command_execution(node->right, env);
			exit(0);
		}
		close(node->fd[1]);
		close(node->fd[0]);
		wait(NULL);
	}
}