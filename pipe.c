/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 17:57:36 by asnaji            #+#    #+#             */
/*   Updated: 2024/01/27 14:39:17 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_path_line(char **envp)
{
	int i;

	i = 0;
	while(envp[i])
	{
		if(ft_strncmp("PATH", envp[i], 4) == 0)
			return (envp[i]);
		i++;
	}
	return (NULL);
}

char *get_working_path(char **envp, char *command)
{
	int i = 0;
	char *line = get_path_line(envp);
	char *tpl = ft_strtrim(line, "PATH=");
	char **paths = ft_split(tpl, ':');
	free(tpl);
	char *acesscheck;
	while(paths[i])
	{
		acesscheck = ft_strjoin(paths[i], "/");
		acesscheck = ft_strjoin(acesscheck, command);
		if(access(acesscheck, X_OK) == 0)
		{
			// ft_free_array(paths);
			return (acesscheck);
		}
		free(acesscheck);
		i++;
	}
	return (NULL);
}

void ft_pipe(char **av, char **envp, char *command, char *command2, char **commandargs1, char **commandargs2) {
    int pipefd[2];
	char *commandwithpath = get_working_path(envp, command);
    pipe(pipefd);
    pid_t child_pid = fork();
	if(child_pid == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		close(pipefd[0]);
		execve(commandwithpath, commandargs1, envp);
	}
	wait(NULL);
	int res = dup(pipefd[0]);
	commandwithpath = get_working_path(envp, command2);
	child_pid = fork();
	if(child_pid == 0)
	{
		dup2(res, STDIN_FILENO);
		execve(commandwithpath, commandargs2, envp);
	}
	// wait(NULL);
	return ;
}
