/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 20:44:21 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/05 15:40:24 by asnaji           ###   ########.fr       */
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

void handle_input(t_token **cmd, char *str, t_env *env)
{
	t_tree	*tree;
	t_tree	*root;
	t_token	*curr;
	t_token *save;
	t_token *new_cmd;
	int		i;
	t_vars *vars;

	vars = malloc(sizeof(t_vars));
	if(!vars)
		return;
	vars->flag = 1;
	vars->i = 0;
	vars->env = env;
	vars->cmd = str;
	curr = *cmd;
	if(str[0])
    {
		exec_heredoc(str);
        if(brackets_check(str) == 1)
        {
            i = ft_switch(cmd, vars);
            if(i == 0)
			{
				give_state_and_type(cmd);
				// curr = *cmd;
				// while(curr)
				// {
				// 	if (curr->cmd)
				// 		printf("token____>|%s|,and space|%d|\n", curr->cmd, curr->spaceafter);
				// 	curr = curr->next;
				// }
			}
			new_cmd = join_args_ifspace(*cmd);
			give_state_and_type(&new_cmd);
        }
        else
            return;
    }
	// printf("\n");
	// printf("\n");
	// printf("\n");
	// printf("\n");
	// printf("\n");
	// printf("\n");
	// if(i == 0)
	// {
	// 	curr = new_cmd;
	// 	while(curr)
	// 	{
	// 		if (curr->cmd)
	// 			printf("token====>|%s|,and its state is|%d|,and its type is|%d|, space after|%d|\n", curr->cmd, curr->state, curr->type, curr->spaceafter);
	// 		curr = curr->next;
	// 	}
	// }
	// return ;
	if(i == 0)
	{
		save = *cmd;
		while(new_cmd->next)
			new_cmd = new_cmd->next;
		root = search_logical_operator(new_cmd);
		// printf("\n");
		// printf("\n");
		// printf("\n");
		// printf("\n");
		// printf("\n");
		// print2D(root);
		// printf("\n");
		// printf("\n");
		// printf("\n");
		// printf("\n");
		// printf("\n");
		// return;
		// find_node_to_execute(root, env);
		andorexecution(root, env);
		free_tree(&root);
		*cmd = save;
	}
}

void f()
{
	system("leaks minishell");
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
			printf("  ==>  %s %d", tmp->cmd, tmp->spaceafter);
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
	t_token				*cmd;
	char				*command;
	char				*pwd;
	struct sigaction	sa;
	t_env				*env_lst;

	// atexit(f);
	(void)ac;
	(void)av;
	env_lst = arr_to_env(env);
	t_env *curr;
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
			print_env(env_lst);
		// if(check_syntax_error(command) == 1)
		handle_input(&cmd, command, env_lst);
		// ft_free_cmd(cmd);
		if (command[0])
			add_history(command);
		free(command);
	}
	free(env_lst);
}
