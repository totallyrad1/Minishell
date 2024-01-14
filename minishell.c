/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 20:44:21 by asnaji            #+#    #+#             */
/*   Updated: 2024/01/14 22:55:33 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void handle_input(t_cmd **cmd, char *str)
// {
// 	tokenizer(cmd, str);
// 	t_cmd *curr = *cmd;
// 	while(curr)
// 	{
// 		if (curr->cmd)
// 			printf("token====>|%s|,and its state is|%d|,and its type is|%d|\n", curr->cmd, curr->state, curr->type);
// 		curr = curr->next;
// 	}
// }

void f()
{
	system("leaks minishell");
}

static t_cmd	*init_cmd()
{
	t_cmd	*cmd;
	
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		exit(2);
	cmd->next = NULL;
	cmd->cmd = NULL;
	return (cmd);
}

char	*get_string_to_print(char **env)
{
	char	*string_to_print;
	char	*pwd;
	char	*pwd_without_home_dir;
	int		len_home_dir;
	char	*home_dir;

	pwd = get_pwd(env);
	home_dir = get_home_dir(env);
	len_home_dir = ft_strlen(home_dir);
	string_to_print = ft_strdup("");
	pwd_without_home_dir = ft_substr(pwd, len_home_dir, ft_strlen(pwd + len_home_dir));
	string_to_print = ft_strjoin(string_to_print, pwd_without_home_dir);
	string_to_print = ft_strjoin(string_to_print, " ");
	free(pwd);
	free(home_dir);
	free(pwd_without_home_dir);
	return (string_to_print);
}

static char	**get_env()
{
	char	*pwd;
	char	**env;
	char	*underscore;

	pwd = getcwd(NULL, 0);
	env = malloc(sizeof(char *) * 3);
	env[0] = ft_strjoin(ft_strdup("PWD="), pwd);
	underscore = ft_strdup("/usr/bin/env");
	env[1] = ft_strjoin(ft_strdup("_="), underscore);
	env[2] = NULL;
	free(pwd);
	return (env);
}

int main(int ac, char **av, char **env)
{
	// t_cmd	*cmd;
	char				*command;
	char				*pwd;
	// char				*string_to_print;
	struct sigaction	sa;

	sa.sa_handler = signal_handler;
	atexit(f);
	if (!(*env))
		env = get_env();
	(void)ac;
	(void)av;
	// atexit(f);
	while (420)
	{
		if (sigaction(SIGINT, &sa, NULL) == -1)
			exit(1);
		// string_to_print = get_string_to_print(env);
		// printf("%s\n", string_to_print);
		// rl_on_new_line();
		// cmd = init_cmd();
		// write(1, string_to_print, ft_strlen(string_to_print));
		// string_to_print = get_string_to_print(env);
		command = readline(">_ Minishell$ ");
		if (!command)
			continue ;
		if (!ft_strncmp(command, "exit", 5))
			exit(0);
		if (!ft_strncmp(command, "pwd", 3))
		{
			pwd = get_pwd(env);
			printf("%s\n", pwd);
			free(pwd);
		}
		if (!ft_strncmp(command, "env", 3))
			print_env(env);
		// if(check_syntax_error(command) == 1)
		// 	handle_input(&cmd, command);
		// ft_free_cmd(cmd);
		add_history(command);
		// free(string_to_print);
		free(command);
	}
}
