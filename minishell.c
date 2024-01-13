/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 20:44:21 by asnaji            #+#    #+#             */
/*   Updated: 2024/01/13 13:30:58 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void handlenput(s_cmd **cmd, char *str)
// {
// 	tokenizer(cmd, str);
// 	s_cmd *curr = *cmd;
// 	while(curr)
// 	{
// 		if (curr->cmd)
// 			printf("token====>|%s|,and its state is|%d|,and its type is|%d|\n", curr->cmd, curr->state, curr->type);
// 		curr = curr->next;
// 	}
// }

void f()
{
	system("leaks minishell");
}

// int main(int ac, char**av, char**env)
// {
// 	s_cmd	*cmd;
// 	char	*command;

// 	atexit(f);
//     while (0 == 0)
// 	{
// 		cmd = malloc(sizeof(s_cmd));
// 		if(!cmd)
// 			exit(2);
// 		cmd->next = NULL;
// 		cmd->cmd = NULL;
// 		command = readline("Minishell~> ");
// 		if (!command)
// 			exit(0);
// 		if(checksyntaxerror(command) == 1)
// 			handlenput(&cmd, command);
// 		ft_freeeverything(cmd);
// 		add_history(command);
// 		free(command);
//     }
// }
