/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxerror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:57:36 by asnaji            #+#    #+#             */
/*   Updated: 2024/01/12 20:31:39 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int checksyntaxerror(char *prompt)
{
	int	i;
	int sc;
	int dc;
	int flag;

	i = 0;
	sc = 0;
	dc = 0;
	flag = 0;
	while(prompt[i])
	{
		if(prompt[i] == '\'' && flag == 0)
		{	
			sc++;
			flag = 2;
		}
		else if(prompt[i] == '\'' && flag == 2)
		{
			flag = 0;
		}
		if(prompt[i] == '"' && flag == 0)
		{	
			dc++;
			flag = 1;
		}
		else if(prompt[i] == '"' && flag == 1)
		{
			flag = 0;
		}
		i++;
	}
	if(flag != 0)
	{		
		printf("Syntax Error\n");
		return 0;
	}
	return 1;
}

// int checkpipesyntax(char *prompt)
// {
// 	int i = 0;
// 	while(prompt[i])
// 	{
		
// 	}
// }

