/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 20:44:21 by asnaji            #+#    #+#             */
/*   Updated: 2024/01/27 22:10:01 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmd(t_tree *root)
{
	t_cmd	*tmp;
	while (root->left)
		root = root->left;
	tmp = root->next;
	while (tmp)
	{
		printf("%s\n", tmp->cmd);
		tmp = tmp->next;
	}
}

void handle_input(t_token **cmd, char *str, char **env)
{
	t_tree	*tree;
	t_tree	*root;
	t_token	*curr;
	t_token *save;
	int		i;
	
	curr = *cmd;
	if(str[0])
    {
		exec_heredoc(str);
        if(brackets_check(str) == 1)
        {
            i = ft_switch(cmd, str, 1, 0);
            if(i == 0)
                give_state_and_type(cmd);
        }
        else
            return;
    }
	// if(i == 0)
	// {
	// 	curr = *cmd;
	// 	while(curr)
	// 	{
	// 		if (curr->cmd)
	// 			printf("token====>|%s|,and its state is|%d|,and its type is|%d|\n", curr->cmd, curr->state, curr->type);
	// 		curr = curr->next;
	// 	}
	// }
	// return ;
	if(i == 0)
	{
		save = *cmd;
		while((*cmd)->next)
			(*cmd) = (*cmd)->next;
		root = search_logical_operator(*cmd);
		// print2D(root);
		// printf("\n");
		findnodetoexecute(root, env);
		free_tree(&root);
		*cmd = save;
	}
}

void f()
{
	system("leaks minishell");
}

static t_token	*init_token()
{
	t_token	*cmd;
	
	cmd = malloc(sizeof(t_token)); 
	if (!cmd)
		exit(2);
	cmd->visited = 0;
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
	t_cmd	*tmp;
    // Base case
    if (root == NULL)
        return;
 
    // Increase distance between levels
    space += 10;
	if (root->next)
	{
		tmp = root->next;
		for (int i = 10; i < space; i++)
			printf(" ");
		while (tmp)
		{
			printf("  ==>  %s", tmp->cmd);
			tmp = tmp->next;
		}
	}
    // Process right child first
	if(root && root->right)
    	print2DUtil(root->right, space);
 
    // Print current node after space
    // count
	if (!root->next)
    {
		printf("\n");
		for (int i = 10; i < space; i++)
			printf(" ");
		printf("%s\n", root->data);
	}
 
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
	t_token	*cmd;
	char				*command;
	char				*pwd;
	struct sigaction	sa;

	// atexit(f);
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
		cmd = init_token();
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
		handle_input(&cmd, command, env);
		ft_free_cmd(cmd);
		add_history(command);
		free(command);
	}
}
