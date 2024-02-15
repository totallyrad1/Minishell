/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   onecommandexec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 17:07:34 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/15 21:48:56 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	if (access(args[0], X_OK) != 0)
		absolutepath = get_working_path(envp, args[0]);
	else
		absolutepath = ft_strdup(args[0]);
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
	t_cmd	*new;
	int		infile;
	int		outfile;

	infile = 0;
	outfile = 1;
	new = new_cmd_list(node->next, env);
	infile = getlastinfile(new, env);
	outfile = getlastoutfile(new);
	if (outfile == -1 || infile == -1)
		return (1);
	args = join_args1(get_command_start(new), env);
	args = get_all_wildcards(args);
	if (!args || !args[0])
		return (0);
	if (is_builtin(args[0]))
		return (builtinexec(args, &env, infile, outfile));
	return (exec_cmd1(infile, outfile, args, env));
}
