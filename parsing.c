/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 19:59:53 by asnaji            #+#    #+#             */
/*   Updated: 2024/01/05 21:36:26 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int checkdelimiter(int c)
{
	if (c == ' ' || c == '\t')
		return 0;
	if (c == '"')
		return 0;
	if (c == '\'' || c == '<' || c == '>')
		return 0;
	if (c == '$' || c == '|')
		return 0;
	return 1;
}

void tokentypedef(char c, int flag, s_cmd **cmd)
{
	s_cmd *curr;
	// static int  0;

	curr = *cmd;
	while(curr->next)
		curr = curr->next;
	if(flag == IN_DQUOTE && c != '"')
		curr->state = IN_DQUOTE;
	if(flag == IN_DQUOTE && c == '"')
		curr->state = IN_DQUOTE;
}

void tokenizer(s_cmd **cmd, char *command)
{
	int tpos;
	int df;
	int i;
	int tnp;
	int c;
	int flag;

	tpos = 0;
	df = 0;
	i = 0;
	tnp = 1;
	c = 0;
	flag = 1;
	while(command[i])
	{
		if(checkdelimiter(command[i]) == 0 || flag == 0)
		{
			if(flag == 1)
				c = command[i];
			tpos = i;
			if((c == '"' || c == '\'') && flag == 1)
			{
				i++;
				flag = 0;
			}
			else if(flag == 0)
			{
				while(command[i] != c && command[i])
					i++;
				flag = 1;
			}
			else if (flag == 1)
			{
				while(command[i] == c && command[i])
					i++;
			}
			df = i;
		}
		else if(checkdelimiter(command[i]) == 1 && flag == 1)
		{
			tpos = i;
			while(checkdelimiter(command[i]) == 1 && command[i])
				i++;
			df = i;
		}
		if(tnp == 1)
		{
			(*cmd)->content = ft_substr(command, tpos, df - tpos);
			tnp = 0;
		}
		else if(command[tpos])
			ft_newnode(cmd, ft_substr(command, tpos, df - tpos));
	}
}
