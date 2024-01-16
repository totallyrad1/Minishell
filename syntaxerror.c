/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxerror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:57:36 by asnaji            #+#    #+#             */
/*   Updated: 2024/01/16 00:43:21 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_syntax_error(char *prompt)
{
	int	i;
	int single_quotes_counter;
	int double_quotes_counter;
	int flag;

	i = 0;
	single_quotes_counter = 0;
	double_quotes_counter = 0;
	flag = 0;
	while (prompt[i])
	{
		if (prompt[i] == '"' && !flag)
		{	
			double_quotes_counter++;
			flag = 1;
		}
		else if (prompt[i] == '"' && flag == 1)
			flag = 0;
		if (prompt[i] == '\'' && !flag)
		{	
			single_quotes_counter++;
			flag = 2;
		}
		else if (prompt[i] == '\'' && flag == 2)
			flag = 0;
		i++;
	}
	if (flag)
	{		
		printf("Syntax Error\n");
		return (0);
	}
	return (1);
}

int all_brackets(char *command, int count, int position)
{
	int i = 0;
	int opencount = 0;
	while(command[i] && i < position)
	{
		if(command[i] == '(')
			opencount++;
		i++;
	}
	if(count - opencount < 0)
		return 1;
	return 0;
}

int brackets_check(char *command)
{
	int i = 0;
	int opencount = 0;
	int closedcount = 0;
	while(command[i])
	{
		if(command[i] == '(')
			opencount++;
		else if(command[i] == ')')
		{
			if(all_brackets(command, closedcount, i) == 0)
			{
				printf("syntax error \n");
				return 0;
			}
			closedcount++;
		}
		i++;
	}
	if(opencount - closedcount != 0)
	{
		printf("syntax error\n");
		return 0;
	}
	return 1;
}

