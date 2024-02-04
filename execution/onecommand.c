/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   onecommand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 10:15:51 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/04 15:17:30 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <assert.h>
#include <stdio.h>

char **join_args(t_tree *root , t_env *env)
{
	char **args;
	int args_size;
	t_cmd *temp;
	int i;
	int tnop = 0;

	args_size = 0;
	i = 0;
	temp = root->next;
	while(temp && temp->cmd && temp->cmd[0] != '<' && temp->cmd[0] != '>')
	{	
		args_size++;
		temp = temp->next;
	}
	args = malloc((args_size + 1) * sizeof(char *));
	if(!args)
		return NULL;
	temp = root->next;
	while(i < args_size && temp && temp->cmd && temp->cmd[0] != '<' && temp->cmd[0] != '>')
	{	
		tnop = 1;
		if(temp && temp->spaceafter != 1)
		{
			while(temp && temp->cmd && temp->spaceafter != 1)
			{
				if(temp->cmd && temp->cmd[0] == '$' && temp->cmd[1] != '\0')
				{
					if(tnop == 1)
					{
						args[i] = ft_strdup(expand(env, &temp->cmd[1]));
						tnop = 0;
					}
					else if(tnop == 0)
						args[i] = ft_strjoin(args[i], expand(env, &temp->cmd[1]));
				}
				else if (temp->cmd)
				{
					if(tnop == 1)
					{
						args[i] = ft_strdup(temp->cmd);	
						tnop = 0;
					}
					else
						args[i] = ft_strjoin(args[i], ft_strdup(temp->cmd));
				}
				temp = temp->next;
			}
			
		}
		else if (temp->spaceafter == 1){
			if(temp->cmd && temp->cmd[0] == '$' && temp->cmd[1] != '\0')
				args[i] = ft_strdup(expand(env, &temp->cmd[1]));
			else
				args[i] = ft_strdup(temp->cmd);
			temp = temp->next;
		}
		i++;
	}
	args[i] = NULL;
	return (args);
}

int one_command_execution(t_tree *node, t_env *env)
{
	char 	*absolutepath;
	char 	**args;
	int 	id;
	char	**envp;
	int status;

	envp = env_to_arr(env);
	args = join_args(node, env);
	if(access(node->data, X_OK) != 0)
		absolutepath = get_working_path(envp, node->data);
	else
		absolutepath = node->data;
	id = fork();
	if(id == -1)
		return 127;
	if(id == 0)
	{
		if(execve(absolutepath, args, envp) != 0)
			printf("invalid command : [%s]\n", args[0]);
		exit(EXIT_FAILURE);
	}
	wait(&status);
	// fprintf(stderr, "%d\n", status);
	return (status);
}



int  andorexecution(t_tree *root, t_env *env)
{
	int status;
	if(root->tree_type == CMD)
		return one_command_execution(root, env);
	else if(root->tree_type == PIPE)
		return pipe_execution(root, env);
	if(root->tree_type == AND)
		return (andorexecution(root->left, env) || andorexecution(root->right, env));
	else if(root->tree_type == OR)
		return (andorexecution(root->left, env) && andorexecution(root->right, env));
	return 127;
}

void find_node_to_execute(t_tree *root , t_env *env)
{
	if(root->tree_type == PIPE)
	{
		pipe_execution(root, env);
			return;
	}
	if(root->tree_type == CMD)
	{
		one_command_execution(root, env);
		return ;
	}
	if(root->left)
		find_node_to_execute(root->left, env);
	if(root->right)
		find_node_to_execute(root->right, env);
}
