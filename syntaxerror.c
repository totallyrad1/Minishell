/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxerror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:57:36 by asnaji            #+#    #+#             */
/*   Updated: 2024/01/13 17:49:52 by yzaazaa          ###   ########.fr       */
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

// int checkpipesyntax(char *prompt)
// {
// 	int i = 0;
// 	while(prompt[i])
// 	{
		
// 	}
// }

