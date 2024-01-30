/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxerror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:57:36 by asnaji            #+#    #+#             */
/*   Updated: 2024/01/23 11:37:47 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	all_brackets(char *command, int count, int position)
{
	int	i;
	int	opencount;

	i = 0;
	opencount = 0;
	while (command[i] && i < position)
	{
		if (command[i] == '(')
			opencount++;
		i++;
	}
	if (count - opencount < 0)
		return (1);
	return (0);
}

int	empty_bracke(char *command, int pos)
{
	int	flag;

	flag = 1;
	pos++;
	while (command[pos] && command[pos] != ')' && islimiter(command[pos]) == 0)
	{
		if (ft_isspace(command[pos]) == 0)
			flag = 0;
		pos++;
	}
	return (flag);
}

int	limiterafter(char *command)
{
	int	i;

	i = 0;
	while (command[i])
		i++;
	i--;
	while (command[i] != ')' && command[i])
		i--;
	while (command[i])
	{
		if (islimiter(command[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}

int	char_after_last_bracket(char *command)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	while (command[i])
		i++;
	i--;
	while (command[i] != ')' && command[i])
		i--;
	if (command[i++] == ')')
		flag = 1;
	while (command[i] && islimiter(command[i]) == 0 && flag == 1)
	{
		if (ft_isspace(command[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	brackets_check(char *command)
{
	int	i;
	int	opencount;
	int	closedcount;
	int	flag;

	i = 0;
	opencount = 0;
	closedcount = 0;
	flag = 0;
	while (command[i] && flag == 0)
	{
		if (command[i] == '(')
		{
			opencount++;
			flag = empty_bracke(command, i);
		}
		else if (command[i] == ')')
		{
			if (all_brackets(command, closedcount, i) == 0)
				return (printf("syntax error \n"), 0);
			closedcount++;
		}
		i++;
	}
	if (char_after_last_bracket(command) == 1 && limiterafter(command) == 0)
		flag = 1;
	if (opencount - closedcount != 0 || flag != 0)
		return (printf("syntax error\n"), 0);
	return (1);
}
