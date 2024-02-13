/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 20:44:21 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/13 13:47:27 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

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

void new_node_heredoc(t_token **cmd, int *flag, int spaceafter ,char *buffer)
{
	t_token *new;
	t_token *curr;

	new = malloc(sizeof(t_token));
	if(!new)
		return ;
	curr = *cmd;
	if(*flag == 1)
	{
		new->cmd = buffer;
		new->spaceafter = spaceafter;
		new->visited = 0;
		new->next = NULL;
		new->prev = NULL;
		*cmd = new;
		*flag = 0;
	}
	else {
		while(curr->next)
			curr = curr->next;
		new->cmd = buffer;
		new->spaceafter = spaceafter;
		new->visited = 0;
		new->next = NULL;
		new->prev = curr;
		curr->next = new;
	}
}


char *removequotesfromheredocargs(char *str)
{
	int i;
	char save;

	i = 0;
	save = str[i++];
	while(str[i] && str[i] != save)		
		i++;
	return ft_substr(str, 1, i - 1);
}

t_token *join_heredocargs(t_token *cmd)
{
	t_token *new;
	char *buffer;
	t_token *curr;
	int spaceafter;
	int flag = 1;

	curr = cmd;
	while(curr)
	{
		if(curr->cmd[0] == '<' && curr->cmd[1] == '<')
		{
			spaceafter = curr->spaceafter;
			buffer = ft_strdup(curr->cmd);
			new_node_heredoc(&new, &flag, spaceafter, buffer);
			buffer = NULL;
			curr = curr->next;
			spaceafter = curr->spaceafter;
			curr->spaceafter = 0;
			while(curr && curr->spaceafter != 1)
			{
				if(curr->cmd[0] == '\'' || curr->cmd[0] == '"')
					buffer = ft_strjoin(buffer, removequotesfromheredocargs(curr->cmd));
				else
					buffer = ft_strjoin(buffer, curr->cmd);
				curr = curr->next;
			}
			new_node_heredoc(&new, &flag, spaceafter, buffer);
		}
		else {
			spaceafter = curr->spaceafter;
			buffer = ft_strdup(curr->cmd);
			new_node_heredoc(&new, &flag, spaceafter, buffer);
			curr=curr->next;
		}
		if(!curr)
			break;
		buffer = NULL;
	}
	return (new);
}

void handle_input(t_token **cmd, char *str, t_env *env)
{
	t_tree	*root;
	t_token *save;
	t_vars *vars;
	t_token *new;
	t_token *save1;

	vars = malloc(sizeof(t_vars));
	if(!vars)
		return;
	vars->flag = 1;
	vars->i = 0;
	vars->env = env;
	vars->cmd = str;
	if(str[0])
    {
		if(ft_switch(cmd, vars) == 0)
		{
			new = join_heredocargs(*cmd);
			give_state_and_type(&new);
			t_token *curr;
				curr = new;
				while(curr)
				{
					if (curr->cmd)
						printf("token====>|%s|,and its state is|%d|,and its type is|%d|\n", curr->cmd, curr->state, curr->type);
					curr = curr->next;
				}
			// return ;
			if(check_syntax_error(&new) == 1)
			{
				save = *cmd;
				save1 = new;
				while(new->next)
					new = new->next;
				root = search_logical_operator(new);
				printf("\n");
				printf("\n");
				printf("\n");
				printf("\n");
				printf("\n");
				print2D(root);
				printf("\n");
				printf("\n");
				printf("\n");
				printf("\n");
				printf("\n");
				// return ;
				andorexecution(root, env);
				free_tree(&root);
				*cmd = save;
			}
		}
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
		printf("%s %d\n", root->data, root->tree_type);
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
	struct sigaction	sa;
	t_env				*env_lst;

	// atexit(f);
	(void)ac;
	(void)av;
	env_lst = arr_to_env(env);
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
			// free_env(env_lst);
			exit(0);
		}
		// if(check_syntax_error(command) == 1)
		handle_input(&cmd, command, env_lst);
		// ft_free_cmd(cmd);
		if (command[0])
			add_history(command);
		free(command);
	}
}
