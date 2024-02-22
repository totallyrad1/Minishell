/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 20:44:21 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/22 20:55:27 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_vars	*init_t_vars(t_env *env, char *str)
{
	t_vars	*vars;

	vars = rad_malloc(sizeof(t_vars), 0, COMMAND);
	vars->flag = 1;
	vars->i = 0;
	vars->env = env;
	vars->cmd = str;
	return (vars);
}

static void	handle_input(t_token **cmd, char *str, t_env *env)
{
	t_tree	*root;
	t_vars	*vars;
	t_token	*new;

	vars = init_t_vars(env, str);
	if (str[0])
	{
		if (tokenizer(cmd, vars) == 0)
		{
			free(str);
			new = join_heredocargs(*cmd);
			give_state_and_type(&new);
			if (check_syntax_error(&new) == 1 && heredocendedwith_c(0, 0) == 0)
			{
				while (new->next)
					new = new->next;
				root = search_logical_operator(new);
				signal(SIGINT, SIG_IGN);
				andorexecution(root, env);
				signal(SIGINT, signal_handler);
				signal(SIGQUIT, SIG_IGN);
			}
		}
	}
}

static void	process(char *command, t_env *env_lst)
{
	t_token	*cmd;

	cmd = init_token();
	if (command[0])
		add_history(command);
	if (onlyspaces(command) == 1)
		handle_input(&cmd, command, env_lst);
	else
		free(command);
	heredocendedwith_c(0, 1);
	rad_malloc(0, 1, COMMAND);
	addfd(0, 0);
}

int	main(int ac, char **av, char **env)
{
	char	*command;
	t_env	*env_lst;

	(void)ac;
	(void)av;
	if (!isatty(ttyslot()))
		return (printf("tty required!\n"), 1);
	env_lst = arr_to_env(env);
	rl_catch_signals = 0;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	while (420)
	{
		command = readline("Turboshell:$ ");
		if (!command)
			exit_with_value(exitstatus(0, 0));
		process(command, env_lst);
	}
	return (0);
}
