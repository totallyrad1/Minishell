/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeexecution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:55:56 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/04 14:01:20 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>
#include <unistd.h>

int pipeexecution1(t_tree *node, t_tree *save, t_env *env)
{
	pid_t id;
	int status = 0;

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
			if(one_command_execution(node->left, env) != 0)
				exit(EXIT_FAILURE);
			exit(0);
		}
		close(save->fd[1]);
		close(save->fd[0]);
		wait(&status);
		if(status != 0)
			return 127;
		save = node;
		return pipeexecution1(node->right, save, env);
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
			if(one_command_execution(node->left, env) != 0)
				exit(EXIT_FAILURE);
			exit(0);
		}
		close(save->fd[1]);
		close(save->fd[0]);
		wait(&status);
		if(status != 0)
			return 127;	
		id = fork();
		if(id == 0)
		{
			close(node->fd[1]);
			dup2(node->fd[0],STDIN_FILENO);
			close(node->fd[0]);
			if(one_command_execution(node->right, env) != 0)
				exit(EXIT_FAILURE);
			exit(0);
		}
		close(save->fd[1]);
		close(save->fd[0]);
		close(node->fd[1]);
		close(node->fd[0]);
		wait(&status);
		if(status != 0)
			return 127;	
	}
	return status;
}

int pipe_execution(t_tree *node, t_env *env)
{
	t_tree *save;
	pid_t id;
	int status= 0;

	if(node->right->tree_type == PIPE)
	{
		pipe(node->fd);
		id = fork();
		if(id == 0)
		{
			close(node->fd[0]);
			dup2(node->fd[1], STDOUT_FILENO);
			close(node->fd[1]);
			if(one_command_execution(node->left, env) != 0)
				exit(EXIT_FAILURE);
			exit(0);
		}
		// close(node->fd[1]);
		// close(node->fd[0]);
		wait(&status);
		if(status != 0)
			return 127;	
		save = node;
		return pipeexecution1(node->right, save, env);
	}
	else {
		pipe(node->fd);
		id = fork();
		if(id == 0)
		{
			close(node->fd[0]);
			dup2(node->fd[1], STDOUT_FILENO);
			close(node->fd[1]);
			if(one_command_execution(node->left, env) != 0)
				exit(EXIT_FAILURE);
			exit(0);
		}
		wait(&status);
		if(status != 0)
			return 127;	
		id = fork();
		if(id == 0)
		{
			close(node->fd[1]);
			dup2(node->fd[0],STDIN_FILENO);
			close(node->fd[0]);
			if(one_command_execution(node->right, env) != 0)
				exit(EXIT_FAILURE);
			exit(0);
		}
		close(node->fd[1]);
		close(node->fd[0]);
		wait(&status);
		if(status != 0)
			return 127;	
	}
	return status;
}