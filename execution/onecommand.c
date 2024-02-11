/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   onecommand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 10:15:51 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/11 16:56:41 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <sys/fcntl.h>

int commandexecution(int i, int flag)
{
	static int s;

	if(flag == 1)
		s = i;
	return s;
}

int	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	if (!ft_strcmp(cmd, "export"))
		return (1);
	if (!ft_strcmp(cmd, "env"))
		return (1);
	if (!ft_strcmp(cmd, "pwd"))
		return (1);
	if (!ft_strcmp(cmd, "unset"))
		return (1);
	if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

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
/* 	if (!ft_strcmp(args[0], "exit"))
		return (ft_exit(args, envp)); */
	return (0);
}

int getlastinfile(t_cmd *cmd)
{
	int fd = 0;
	t_cmd *curr;

	curr = cmd;
	while(curr)
	{
		if(curr->cmd[0] == '<')
		{
			fd = open(curr->next->cmd , O_RDONLY);
		}
		curr = curr->next;
	}
	return fd;
}

int getlastoutfile(t_cmd *cmd)
{
	int fd = 1;
	t_cmd *curr;

	curr = cmd;
	while(curr)
	{
		if(curr->cmd[0] == '>')
		{
			fd = open(curr->next->cmd , O_CREAT | O_WRONLY, 0777);
		}
		curr = curr->next;
	}	
	return fd;
}

void changeinfile(int fd)
{
	if(fd != 0)
	{
		// write(2, "changed in file\n", ft_strlen("changed in file\n"));
		dup2(fd,STDIN_FILENO);
		close(fd);
	}
}

void changeoutfile(int fd)
{
	if(fd != 1)
	{
		// write(2, "changed out file\n", ft_strlen("changed out file\n"));
		dup2(fd,STDOUT_FILENO);
		close(fd);
	}
}

void resetfds()
{
	dup2(0, STDIN_FILENO);
	dup2(1, STDOUT_FILENO);
}

int one_command_execution(t_tree *node, t_env *env)
{
	char	*absolutepath;
	char	**args;
	pid_t	id;
	char	**envp;
	int		status;

	
	int infile = 0;
	int outfile = 1;
	infile = getlastinfile(node->next);
	// printf("infile ==>%d\n", infile);
	outfile = getlastoutfile(node->next);
	// printf("outfile ==>%d\n", outfile);
	
	args = join_args1(node, env);
	envp = env_to_arr(env);
	if (is_builtin(args[0]))
		return (exec_builtin(args, &env));
	if(access(args[0], X_OK) != 0)
		absolutepath = get_working_path(envp, args[0]);
	else
		absolutepath = ft_strdup(args[0]);
	id = fork();
	if(id == -1)
		return (127);
	if(id == 0)
	{
		changeinfile(infile);
		changeoutfile(outfile);
		if(execve(absolutepath, args, envp) != 0)
		{
			write(2, "turboshell: command not found: ", ft_strlen("turboshell: command not found: "));
			write(2, args[0], ft_strlen(args[0]));
			write(2, "\n", 1);
		}
		exit(127);
	}
	wait(&status);
	exitstatus(WEXITSTATUS(status), 1);
	// ft_free_array(args);
	return ( free(absolutepath), status);
}

int  andorexecution(t_tree *root, t_env *env)
{
	if (root->tree_type == CMD)
		return one_command_execution(root, env);
	else if (root->tree_type == PIPE)
		return improvedpipeexecution(root, env);
	if (root->tree_type == AND)
		return (andorexecution(root->left, env) || andorexecution(root->right, env));
	else if (root->tree_type == OR)
		return (andorexecution(root->left, env) && andorexecution(root->right, env));
	return 127;
}
