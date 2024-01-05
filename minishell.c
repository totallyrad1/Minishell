/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 20:44:21 by asnaji            #+#    #+#             */
/*   Updated: 2024/01/05 16:53:27 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handlenput(s_cmd **cmd, char *str)
{
	tokenizer(cmd, str);
	s_cmd *curr = *cmd;
	while(curr)
	{
		if (curr->content)
			printf("this ====>%s\n", curr->content);
		curr = curr->next;
	}
}

void f()
{
			system("leaks minishell");
	
}

int main()
{
	s_cmd	*cmd;
	char	*command;

	atexit(f);
    while (0 == 0)
	{
		cmd = malloc(sizeof(s_cmd));
		if(!cmd)
			exit(2);
		cmd->next = NULL;
		cmd->content = NULL;
		command = readline("Minishell~> ");
		if (!command)
		{
			exit(0);
		}
		if(checksyntaxerror(command) == 1)
			handlenput(&cmd, command);
		ft_freeeverything(cmd);
		add_history(command);
		free(command);
    }
}
