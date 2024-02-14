/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   onecommand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 10:15:51 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/14 11:09:12 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <sys/fcntl.h>
#include <unistd.h>

int commandexecution(int i, int flag)
{
	static int s;

	if(flag == 1)
		s = i;
	return s;
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
	if (!ft_strcmp(args[0], "cd"))
		return (ft_cd(args, envp));
	if (!ft_strcmp(args[0], "echo"))
		return (ft_echo(args, envp));
	if (!ft_strcmp(args[0], "export"))
		return (ft_export(args, envp));
	if (!ft_strcmp(args[0], "env"))
	{
		print_env(*envp);
		return (0);
	}
	if (!ft_strcmp(args[0], "pwd"))
	{
		get_pwd(*envp);
		return (0);
	}
	if (!ft_strcmp(args[0], "unset"))
		return (unset(args, envp));
/* 	if (!ft_strcmp(args[0], "exit"))
		return (ft_exit(args, envp)); */
	return (0);
}


int getlastinfile(t_cmd *cmd, t_env *env)
{
	int fd = 0;
	t_cmd *curr;

	curr = cmd;
	while(curr)
	{
		if(curr->cmd[0] == '<' && curr->cmd[1] == '<')
		{
			if(curr->expand == 0)
				fd = heredoc_expanded(curr->heredocfd, env);
			else
				fd = curr->heredocfd;
		}
		else if(curr->cmd[0] == '<' && curr->cmd[1] == '\0')
			fd = open(curr->next->cmd , O_RDONLY);
		curr = curr->next;
	}
	return fd;
}

int getlastoutfile(t_cmd *cmd)
{
	int fd = 1;
	t_cmd *curr;

	curr = cmd;
	while(curr)
	{
		if(curr->cmd[0] == '>' && curr->cmd[1] == '>')
		{
			fd = open(curr->next->cmd , O_CREAT | O_WRONLY | O_APPEND, 0777);
		}
		else if(curr->cmd[0] == '>' && curr->cmd[1] == '\0')
		{
			fd = open(curr->next->cmd , O_CREAT | O_WRONLY | O_TRUNC, 0777);
		}
		curr = curr->next;
	}	
	return fd;
}

void changeinfile(int fd)
{
	if(fd != 0)
	{
		dup2(fd,STDIN_FILENO);
		close(fd);
	}
}

void changeoutfile(int fd)
{
	if(fd != 1)
	{
		dup2(fd,STDOUT_FILENO);
		close(fd);
	}
}

void resetfds()
{
	dup2(0, STDIN_FILENO);
	dup2(1, STDOUT_FILENO);
}

t_cmd *get_command_start(t_cmd *node)
{
	t_cmd *curr;
	
	curr = node;

	if(curr->cmd[0] != '<' && curr->cmd[0] != '>')
		return curr;
	else
	{
	 	while(curr)
		{
			if(curr->cmd[0] != '<' && curr->cmd[0] != '>' && curr->next && curr->next->cmd[0] != '<' && curr->next->cmd[0] != '>')
			{
				curr = curr->next;
				return curr;
			}
			curr = curr->next;
		}
	}
	return curr;
}

void new_cmd_node(int *flag, t_cmd **cmd, char *buffer, int spaceafter, int heredocfd, int forheredoc)
{
	t_cmd *new;
	t_cmd *curr;
	
	curr = *cmd;
	new = malloc(sizeof(t_cmd));
	if(!new)
		return ;
	if(*flag == 1)
	{
		new->cmd = buffer;
		new->next = NULL;
		new->heredocfd = heredocfd;
		new->expand = forheredoc;
		new->spaceafter = spaceafter;
		*flag = 0;
		*cmd = new;
	}
	else {
		while(curr->next)
			curr = curr->next;
		new->cmd = buffer;
		new->next = NULL;
		new->heredocfd = heredocfd;
		new->expand = forheredoc;
		new->spaceafter = spaceafter;
		curr ->next = new;
	}
}

t_cmd *new_cmd_list(t_cmd *root , t_env *env)
{
	t_cmd *new;
	t_cmd *curr;
	char *buffer;
	int flag = 1;
	int spaceafter;
	int heredocfd;
	int forheredoc;

	buffer = NULL;
	curr = root;
	forheredoc = 0;
	while(curr)
	{
		if(curr->cmd[0] == '<' || curr->cmd[0] == '>')
		{
			forheredoc = curr->expand;
			spaceafter = curr->spaceafter;
			heredocfd = curr->heredocfd;
			buffer = ft_strdup(curr->cmd);
			new_cmd_node(&flag, &new, buffer, spaceafter, heredocfd, forheredoc);
			buffer = NULL;
			curr = curr->next;
			forheredoc = curr->expand;
			spaceafter = curr->spaceafter;
			heredocfd = curr->heredocfd;
			curr->spaceafter = 0;
			while(curr && curr->spaceafter != 1 && curr->cmd[0] != '>' && curr->cmd[0] != '<')
			{
				buffer = ft_strjoin(buffer, argextraction(curr, env));
				curr = curr->next;
			}
			new_cmd_node(&flag, &new, buffer, spaceafter, heredocfd, forheredoc);
		}
		else {
			forheredoc = curr->expand;
			spaceafter = curr->spaceafter;
			heredocfd = curr->heredocfd;
			buffer = ft_strdup(curr->cmd);
			new_cmd_node(&flag, &new, buffer, spaceafter, heredocfd, forheredoc);
			curr=curr->next;
		}
		if(!curr)
			break;
		buffer = NULL;
	}
	return new;
}

int one_command_execution(t_tree *node, t_env *env)
{
	char	*absolutepath;
	char	**args;
	pid_t	id;
	char	**envp;
	int		status;
	t_cmd *new;

	
	int infile = 0;
	int outfile = 1;
	new = new_cmd_list(node->next, env);
	infile = getlastinfile(new, env);
	outfile = getlastoutfile(new);
	args = join_args1(get_command_start(new), env);
	if(!args)
		return 0;
	envp = env_to_arr(env);
	if (is_builtin(args[0]))
		return (exec_builtin(args, &env));
	if(access(args[0], X_OK) != 0)
		absolutepath = get_working_path(envp, args[0]);
	else
		absolutepath = ft_strdup(args[0]);
	id = fork();
	if(id == -1)
		return (127);
	if(id == 0)
	{
		changeinfile(infile);
		changeoutfile(outfile);
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
	if (root->tree_type == AND)
		return (andorexecution(root->left, env) || andorexecution(root->right, env));
	else if (root->tree_type == OR)
		return (andorexecution(root->left, env) && andorexecution(root->right, env));
	else if (root->tree_type == PIPE)
		return improvedpipeexecution(root, env);
	else
		return one_command_execution(root, env);
	return 127;
}
