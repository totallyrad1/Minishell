/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 20:44:21 by asnaji            #+#    #+#             */
/*   Updated: 2024/01/21 23:18:56 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_input(t_cmd **cmd, char *str)
{
	t_tree	*tree;
	t_tree	*root;
	t_cmd	*curr;
	int		i;
	t_cmd *save;
	
	curr = *cmd;
	if(str[0])
    {
        if(brackets_check(str) == 1)
        {
            i = ft_switch(cmd, str, 1, 0);
            if(i == 0)
                give_state_and_type(cmd);
        }
        else
            return;
    }
	save = *cmd;
	while((*cmd)->next)
		(*cmd) = (*cmd)->next;
	root = search_logical_operator(*cmd);
	print2D(root);
	free_tree(&root);
	*cmd = save;
}

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
	cmd->prev = NULL;
	return (cmd);
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

void print2DUtil(t_tree* root, int space)
{
    // Base case
    if (root == NULL)
        return;
 
    // Increase distance between levels
    space += 10;
 
    // Process right child first
	if(root && root->right)
    	print2DUtil(root->right, space);
 
    // Print current node after space
    // count
    printf("\n");
    for (int i = 10; i < space; i++)
        printf(" ");
    printf("%s\n", root->data);
 
    // Process left child
	if(root && root->left)
		print2DUtil(root->left, space);
}
 
// Wrapper over print2DUtil()
void print2D(t_tree* root)
{
    print2DUtil(root, 0);
}

int main(int ac, char **av, char **env)
{
	t_cmd	*cmd;
	char				*command;
	char				*pwd;
	struct sigaction	sa;

	atexit(f);
	(void)ac;
	(void)av;
	if (!(*env))
		env = get_env();
	rl_catch_signals = 0;
	sa.sa_handler = signal_handler;
	while (420)
	{
		if (sigaction(SIGINT, &sa, NULL) == -1)
			exit(1);
		if (sigaction(SIGQUIT, &sa, NULL) == -1)
			exit(1);
		cmd = init_cmd();
		command = readline(">_ Turboshell$ ");
		if (!command)
		{
			printf("exit\n");
			exit(0);
		}
		if (!ft_strncmp(command, "clear", 5))
			write(1, "\033[H\033[J", 7);
		if (!ft_strncmp(command, "exit", 5))
		{
			printf("exit\n");
			ft_free_cmd(cmd);
			free(command);
			exit(0);
		}
		if (!ft_strncmp(command, "pwd", 3))
		{
			pwd = get_pwd(env);
			printf("%s\n", pwd);
			free(pwd);
		}
		if (!ft_strncmp(command, "env", 3))
			print_env(env);
		// if(check_syntax_error(command) == 1)
		handle_input(&cmd, command);
		ft_free_cmd(cmd);
		add_history(command);
		free(command);
	}
}
