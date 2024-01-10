/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 17:57:36 by asnaji            #+#    #+#             */
/*   Updated: 2024/01/10 19:48:44 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *getpathline(char **envp)
{
	int i;

	i = 0;
	while(envp[i])
	{
		if(ft_strncmp("PATH", envp[i], 4) == 0)
			return envp[i];
		i++;
	}
	return NULL;
}

char *getworkingpath(char **envp, char *command)
{
	int i = 0;
	char *line = getpathline(envp);
	char *tpl = ft_strtrim(line, "PATH=");
	// free(line);
	char **paths = ft_split(tpl, ':');
	// int j = 0;
	// free(tpl);
	char *acesscheck;
	while(paths[i])
	{
		acesscheck = ft_strjoin(paths[i], "/");
		acesscheck = ft_strjoin(acesscheck, command);
		// printf("%s\n", acesscheck);
		if(access(acesscheck, X_OK) == 0)
		{
			// freemem(paths);
			return acesscheck;
		}
		// free(acesscheck);
		i++;
	}
	return NULL;
}

void ft_pipe(char **av, char **envp, char *command, char *command2, char **commandargs1, char **commandargs2) {
    int pipefd[2];
    pipe(pipefd);
	char *commandwithpath = getworkingpath(envp, command);
    pid_t child_pid = fork();
	if(child_pid == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		close(pipefd[0]);
		execve(commandwithpath, commandargs1, envp);
	}
	wait(NULL);
	int res = pipefd[0];
	commandwithpath = getworkingpath(envp, command2);
	child_pid = fork();
	if(child_pid == 0)
	{
		dup2(res, STDIN_FILENO);
		execve(commandwithpath, commandargs2, envp);
	}
	// wait(NULL);
	return ;
}