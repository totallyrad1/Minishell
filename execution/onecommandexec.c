/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   onecommandexec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 17:07:34 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/18 12:46:18 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
// #include <cstddef>

void	execute_cmd(char *abpath, char **envp, char **args)
{
	if (execve(abpath, args, envp) != 0)
	{
		wrerror("turboshell: command not found: ");
		wrerror(args[0]);
		wrerror("\n");
	}
	exit(127);
}

int	exec_cmd1(int infile, int outfile, char **args, t_env *env)
{
	pid_t	id;
	int		status;
	char	*absolutepath;
	char	**envp;

	envp = env_to_arr(env);
	if (access(args[0], F_OK) != 0)
		absolutepath = get_working_path(envp, args[0]);
	else
		absolutepath = ft_strdup(args[0]);
	if(access(absolutepath, F_OK) == 0 && access(absolutepath, X_OK) != 0)
	{
		wrerror("turboshell :permission denied: ");
		wrerror(args[0]);
		wrerror("\n");
		exitstatus(126, 1);
		return (126);
	}
	id = fork();
	if (id == -1)
	{
		wrerror("turboshell: fork: Resource temporarily unavailable\n");
		return (127);
	}
	if (id == 0)
	{
		changeinfile(infile);
		changeoutfile(outfile);
		execute_cmd(absolutepath, envp, args);
	}
	wait(&status);
	exitstatus(WEXITSTATUS(status), 1);
	return (status);
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
	new_joinedargs = joined_args(lst_args, env);
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
