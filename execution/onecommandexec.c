/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   onecommandexec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 17:07:34 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/22 20:59:00 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	execute_cmd(char *abpath, char **envp, char **args)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (execve(abpath, args, envp) != 0)
	{
		wrerror("turboshell: ");
		wrerror(args[0]);
		if (((ft_strchr(args[0], '/') || ft_strchr(args[0], '\\'))
				&& access(abpath, F_OK) != 0) || abpath == NULL)
			wrerror(": no such file or directory");
		else if (access(abpath, F_OK) == 0)
			wrerror(": cant execute this file");
		else
			wrerror(": command not found");
		wrerror("\n");
		exit(127);
	}
}

static int	getabpath(char **envp, char *command, char **abpath)
{
	struct stat	filestat;

	if (ft_strchr(command, '/') || ft_strchr(command, '\\'))
	{
		*abpath = ft_strdup(command);
		if (stat(*abpath, &filestat) == 0 && S_ISDIR(filestat.st_mode))
		{
			wrerror(*abpath);
			wrerror(" :is a Directory\n");
			return (exitstatus(126, 1));
		}
	}
	else
		*abpath = get_working_path(envp, command);
	if (access(*abpath, F_OK) == 0 && access(*abpath, X_OK) != 0)
	{
		wrerror("permission denied: ");
		wrerror(command);
		wrerror("\n");
		return (exitstatus(126, 1));
	}
	return (exitstatus(0, 1));
}

void	setexit(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 3)
		{
			printf("Quit: 3\n");
			reset_terminal();
		}
		else
			printf("\n");
		exitstatus(WTERMSIG(status) + 128, 1);
	}
	else
		exitstatus(WEXITSTATUS(status), 1);
}

static int	exec_cmd1(int infile, int outfile, char **args, t_env *env)
{
	pid_t	id;
	int		status;
	char	*absolutepath;
	char	**envp;

	envp = env_to_arr(env);
	if (getabpath(envp, args[0], &absolutepath) != 0)
		return (exitstatus(0, 0));
	id = fork();
	if (id == -1)
		return (wrerror(FORK_ERROR), ft_exit(NULL), 0);
	if (id == 0)
	{
		changeinfile(infile);
		changeoutfile(outfile);
		execute_cmd(absolutepath, envp, args);
	}
	while (waitpid(-1, &status, 0) != -1)
		;
	setexit(status);
	return (exitstatus(0, 0));
}

int	one_command_execution(t_tree *node, t_env *env)
{
	char	**args;
	int		infile;
	int		outfile;
	t_cmd	*lst_args;
	t_cmd	*new_joinedargs;

	infile = 0;
	outfile = 1;
	lst_args = make_args_lst(new_cmd_list(node->next, env), env);
	new_joinedargs = joined_args(lst_args);
	args = get_all_wildcards(new_joinedargs);
	getfds(lst_args, env, &infile, &outfile);
	if (outfile == -1 || infile == -1)
		return (1);
	if (!args || !args[0])
		return (0);
	if (!ft_strcmp(args[0], "env") && args[1])
		return (exitstatus(1, 1), 1);
	else if (is_builtin(args[0]))
		return (builtinexec(args, &env, infile, outfile));
	return (exec_cmd1(infile, outfile, args, env));
}
