/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   onecommand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 10:15:51 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/03 06:21:45 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char **join_args(t_tree *root , t_env *env)
{
	char **args;
	int args_size;
	t_cmd *temp;
	int i;

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
	while(temp && temp->cmd && temp->cmd[0] != '<' && temp->cmd[0] != '>')
	{	
		if(temp->cmd[0] == '$' && ft_alphanum(temp->cmd[1]))
		{
			args[i] = expand(env, &temp->cmd[1]);
		}
		else {
			args[i] = ft_strdup(temp->cmd);
		}
		i++;
		temp = temp->next;
	}
	args[args_size] = NULL;
	return (args);
}

void one_command_execution(t_tree *node, t_env *env)
{
	char 	*absolutepath;
	char 	**args;
	int 	id;
	char	**envp;

	envp = env_to_arr(env);
	args = join_args(node, env);
	if(access(node->data, X_OK) != 0)
		absolutepath = get_working_path(envp, node->data);
	else
		absolutepath = node->data;
	id = fork();
	if(id == -1)
		return;
	if(id == 0)
	{
		if(execve(absolutepath, args, envp) != 0)
			printf("invalid command : [%s]\n", args[0]);
		exit(EXIT_FAILURE);
	}
	wait(NULL);
	// free(absolutepath);
	ft_free_array(args);
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
