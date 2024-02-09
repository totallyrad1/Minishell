/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   onecommand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 10:15:51 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/09 09:42:54 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char **join_args1(t_tree *root , t_env *env)
{
	char **args;
	int args_size;
	t_cmd *temp;
	int i;
	int firstit = 0;

	args_size = 0;
	i = -1;
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
	temp->spaceafter = 1;
	while(i < args_size && temp && temp->cmd && temp->cmd[0] != '<' && temp->cmd[0] != '>')
	{
		if(temp->spaceafter == 1)
		{
			i++;
			firstit = 0;
		}
		if (firstit == 0)
		{
			if (temp->cmd && (temp->cmd[0] == '"' || temp->cmd[0] == '\''))
				args[i] = quotes_toexpression(temp->cmd, env);
			else if (temp->cmd && temp->cmd[0] == '$')
				args[i] = ft_strdup(expand(env, &temp->cmd[1]));
			else
				args[i] = ft_strdup(temp->cmd);
			firstit = 1;
		}
		else 
		{
			if (temp->cmd && (temp->cmd[0] == '"' || temp->cmd[0] == '\''))
				args[i] = ft_strjoin(args[i], quotes_toexpression(temp->cmd, env));
			else if (temp->cmd && temp->cmd[0] == '$')
				args[i] = ft_strjoin(args[i], expand(env, &temp->cmd[1]));
			else
				args[i] = ft_strjoin(args[i], ft_strdup(temp->cmd));
		}
		temp = temp->next;
	}
	i++;
	args[i] = NULL;
	return (args);
}

int	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	if (!ft_strcmp(cmd, "export"))
		return (1);
	if (!ft_strcmp(cmd, "env"))
		return (1);
	if (!ft_strcmp(cmd, "pwd"))
		return (1);
	if (!ft_strcmp(cmd, "unset"))
		return (1);
	if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

int	exec_builtin(char **args, t_env **envp)
{
	char	*pwd_str;

	if (!ft_strcmp(args[0], "cd"))
		return (ft_cd(args, envp));
	if (!ft_strcmp(args[0], "echo"))
		return (ft_echo(args));
	if (!ft_strcmp(args[0], "export"))
		return (ft_export(args, envp));
	if (!ft_strcmp(args[0], "env"))
	{
		print_env(*envp);
		return (0);
	}
	if (!ft_strcmp(args[0], "pwd"))
	{
		pwd_str = get_pwd();
		printf("%s\n", pwd_str);
		return (free(pwd_str), 0);
	}
	if (!ft_strcmp(args[0], "unset"))
		return (unset(args, envp));
/* 	if (!ft_strcmp(args[0], "exit"))
		return (ft_exit(args, envp)); */
	return (0);
}

int one_command_execution(t_tree *node, t_env *env)
{
	char	*absolutepath;
	char	**args;
	pid_t	id;
	char	**envp;
	int		status;

	args = join_args1(node, env);
	envp = env_to_arr(env);
	if (is_builtin(args[0]))
		return (exec_builtin(args, &env));
	if(access(node->data, X_OK) != 0)
		absolutepath = get_working_path(envp, args[0]);
	else
		absolutepath = ft_strdup(args[0]);
	id = fork();
	if(id == -1)
		return (127);
	if(id == 0)
	{
		if(execve(absolutepath, args, envp) != 0)
		{
			write(2, "turboshell: command not found: ", ft_strlen("turboshell: command not found: "));
			write(2, args[0], ft_strlen(args[0]));
			write(2, "\n", 1);
		}
		exit(127);
	}
	wait(&status);
	exitstatus(WEXITSTATUS(status), 1);
	return (ft_free_array(args), free(absolutepath), status);
}

int  andorexecution(t_tree *root, t_env *env)
{
	if (root->tree_type == CMD)
		return one_command_execution(root, env);
	else if (root->tree_type == PIPE)
		return improvedpipeexecution(root, env);
	if (root->tree_type == AND)
		return (andorexecution(root->left, env) || andorexecution(root->right, env));
	else if (root->tree_type == OR)
		return (andorexecution(root->left, env) && andorexecution(root->right, env));
	return 127;
}
