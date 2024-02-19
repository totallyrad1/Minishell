/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 20:44:21 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/19 22:44:20 by yzaazaa          ###   ########.fr       */
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

void	new_node_heredoc(t_token **cmd, int *flag, int spaceafter ,char *buffer, int forheredoc)
{
	t_token *new;
	t_token *curr;

	new = rad_malloc(sizeof(t_token), 0, COMMAND);
	if(!new)
		return (ft_exit(NULL));
	curr = *cmd;
	if(*flag == 1)
	{
		new->cmd = buffer;
		new->spaceafter = spaceafter;
		new->for_heredoc = forheredoc;
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
		new->for_heredoc = forheredoc;
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
	while (str[i] && str[i] != save)		
		i++;
	return (ft_substr(str, 1, i - 1));
}

t_token *join_heredocargs(t_token *cmd)
{
	t_token *new;
	char *buffer;
	t_token *curr;
	int spaceafter;
	int flag = 1;
	int forheredoc;

	curr = cmd;
	forheredoc = 0;
	while(curr)
	{
		if(curr->cmd[0] == '<' && curr->cmd[1] == '<' && curr->next && islimiter1(curr->next->cmd[0]) == 0)
		{
			spaceafter = curr->spaceafter;
			buffer = ft_strdup(curr->cmd);
			new_node_heredoc(&new, &flag, spaceafter, buffer, forheredoc);
			buffer = NULL;
			curr = curr->next;
			spaceafter = curr->spaceafter;
			curr->spaceafter = 0;
			forheredoc = 0;
			while(curr && curr->spaceafter != 1 && islimiter1(curr->cmd[0]) == 0)
			{
				if(curr->cmd[0] == '\'' || curr->cmd[0] == '"')
				{
					forheredoc = 1;
					buffer = ft_strjoin(buffer, removequotesfromheredocargs(curr->cmd));
				}
				else if(curr->cmd[0] == '$' && !curr->cmd[1] && curr->next)
				{
					if(curr->next && curr->next->cmd[0] != '"' && curr->next->cmd[0] != '\'')
						buffer = ft_strjoin(buffer, curr->cmd);
				}
				else
					buffer = ft_strjoin(buffer, curr->cmd);
				curr = curr->next;
			}
			new_node_heredoc(&new, &flag, spaceafter, buffer, forheredoc);
		}
		else 
		{
			spaceafter = curr->spaceafter;
			buffer = ft_strdup(curr->cmd);
			new_node_heredoc(&new, &flag, spaceafter, buffer, forheredoc);
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
	t_vars *vars;
	t_token *new;

	vars = rad_malloc(sizeof(t_vars), 0, COMMAND);
	if(!vars)
		ft_exit(NULL);
	vars->flag = 1;
	vars->i = 0;
	vars->env = env;
	vars->cmd = str;
	if(str[0])
    {
		if(ft_switch(cmd, vars) == 0)
		{
			free(str);
			new = join_heredocargs(*cmd);
			// t_token *curr;
			// curr = new;
			// while(curr)
			// {
			// 	printf("%s\n", curr->cmd);
			// 	curr =curr->next;
			// }
			give_state_and_type(&new);
			if(check_syntax_error(&new) == 1)
			{
				while(new->next)
					new = new->next;
				root = search_logical_operator(new);
				signal(SIGINT, SIG_IGN);
				andorexecution(root, env);
				signal(SIGINT, signal_handler);
				signal(SIGQUIT, SIG_DFL);
			}
		}
    }
}

void f()
{
	system("leaks minishell > hh");
}

int onlyspaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int main(int ac, char **av, char **env)
{
	t_token				*cmd;
	char				*command;
	t_env				*env_lst;
	
	// atexit(f);
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
		cmd = init_token();
		command = readline(">_ Turboshell$ ");
		if (!command)
			ft_exit(NULL);
		if (command[0])
			add_history(command);
		if(onlyspaces(command) == 1)
			handle_input(&cmd, command, env_lst);
		else
			free(command);
	}
	return (0);
}
