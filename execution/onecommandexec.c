/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   onecommandexec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 17:07:34 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/20 19:04:44 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_cmd(char *abpath, char **envp, char **args)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (execve(abpath, args, envp) != 0)
	{
		wrerror("turboshell: command not found: ");
		wrerror(args[0]);
		wrerror("\n");
		exit(127);
	}
}

int getabpath(char **envp, char *command , char **abpath)
{
	struct stat	filestat;
	
	if (access(command, F_OK) != 0)
		*abpath = get_working_path(envp, command);
	else
	{
		*abpath = ft_strdup(command);
		if (stat(*abpath, &filestat) == 0)
		{
       		if (S_ISDIR(filestat.st_mode))
          	{
				wrerror(*abpath);
				wrerror(" :is a Directory\n");
				return (exitstatus(126, 1));
			}
		}
	}
	if (access(*abpath, F_OK) == 0 && access(*abpath, X_OK) != 0)
	{
		wrerror("permission denied: ");
		wrerror(command);
		wrerror("\n");
		return (exitstatus(126, 1));
	}
	return (exitstatus(0, 1));
}


int	exec_cmd1(int infile, int outfile, char **args, t_env *env)
{
	pid_t	id;
	int		status;
	char	*absolutepath;
	char	**envp;

	envp = env_to_arr(env);
	if(getabpath(envp, args[0], &absolutepath) != 0)
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
	if (WIFSIGNALED(status))
    {
        if (WTERMSIG(status) == 3)
            printf("Quit: 3\n");
        else
            printf("\n");
        exitstatus(WTERMSIG(status) + 128, 1);
    }
	else
        exitstatus(WEXITSTATUS(status), 1);
	return (exitstatus(0, 0));
}

int	one_command_execution(t_tree *node, t_env *env)
{
	char	**args;
	int		infile;
	int		outfile;
	t_cmd	*lst_args;
	t_cmd	*new_joinedargs;
	t_cmd	*new;

	infile = 0;
	outfile = 1;
	new = new_cmd_list(node->next, env);
	lst_args = make_args_lst(new, env);
	new_joinedargs = joined_args(lst_args);
	args = get_all_wildcards(new_joinedargs);
	getfds(lst_args, env, &infile, &outfile);
	if (outfile == -1 || infile == -1)
		return (1);
	if (!args || !args[0])
		return (0);
	if (is_builtin(args[0]))
		return (builtinexec(args, &env, infile, outfile));
	return (exec_cmd1(infile, outfile, args, env));
}
