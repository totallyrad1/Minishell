/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 19:59:53 by asnaji            #+#    #+#             */
/*   Updated: 2024/01/06 16:10:57 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void fill_node(int start, int len, char *command, s_cmd **cmd, int *tnp, int state, int type)
{
	if(*tnp == 1)
	{
		(*cmd)->content = ft_substr(command, start, len);
		(*cmd)->type = type;
		(*cmd)->state = state;
		*tnp = 0;
	}
	else
	 	ft_newnode(cmd, ft_substr(command, start, len), type, state);
}

int getlimitertoken(char c, char f)
{
	if (c == '"')
		return TOKEN_D_Q;
	if (c == '\'')
		return TOKEN_S_Q;
	if (c == '<')
	{
		if(f == '<')
			return TOKEN_HEREDOC;
		return TOKEN_REDIR_IN;
	}
	if (c == '>')
	{
		if(f == '>')
			return TOKEN_REDIR_APPEND;
		return TOKEN_REDIR_OUT;
	}
	if (c == '|')
		return TOKEN_PIPE;
	if (c == '$')
		return TOKEN_DOLLAR;
	return 10;
}

void tokenizer(s_cmd **cmd, char *command)
{
	int tpos = 0;
	int df = 0;
	int i = 0;;
	int tnp = 1;
	char save;
	int wordfound = 0;
	int type = 0;
	int state = 0;
	
	while(command[i])
	{
		tpos = i;
		while(ft_isspace(command[i]) == 0 && islimiter(command[i]) == 0 && ft_isquote(command[i]) == 0 &&command[i])
		{	
			wordfound = 1;
			i++;
			type = TOKEN_EXPR;
			state = GENERAL;
		}
		df = i;
		if(wordfound == 1)
			fill_node(tpos, df - tpos, command, cmd, &tnp, state , type);
		wordfound = 0;
		tpos = i;
		while(ft_isspace(command[i]) == 1 && islimiter(command[i]) == 0 && ft_isquote(command[i]) == 0 &&command[i])
		{	
			wordfound = 1;
			i++;
			type = TOKEN_SPACE;
			state = GENERAL;
		}
		df = i;
		if(wordfound == 1)
			fill_node(tpos, df - tpos, command, cmd, &tnp, state, type);
		wordfound = 0;
		if(ft_isquote(command[i]) == 1)
		{
			tpos = i;
			save = command[i++];
			df = i;
			if(save == '\'')
			{
				state = GENERAL;
				type = TOKEN_S_Q;
			}
			else if(save == '"')
			{
				state = GENERAL;
				type = TOKEN_D_Q;
			}
			fill_node(tpos, df - tpos, command, cmd, &tnp, state, type);
			tpos = i;
			while(command[i] != save && command[i])
			{
				i++;
				wordfound = 1;
				if(save == '\'')
				{
					state = IN_QUOTE;
					type = TOKEN_EXPR;
				}
				else if(save == '"')
				{
					state = IN_DQUOTE;
					type = TOKEN_EXPR;
				}
			}
			df = i;
			if(wordfound == 1)
				fill_node(tpos, df - tpos, command, cmd, &tnp, state, type);
			wordfound = 0;
			tpos = i;
			i++;
			df = i;
			if(save == '\'')
			{
				state = GENERAL;
				type = TOKEN_S_Q;
			}
			else if(save == '"')
			{
				state = GENERAL;
				type = TOKEN_D_Q;
			}
			fill_node(tpos, df - tpos, command, cmd, &tnp, state, type);
		}
		tpos = i;
		while(ft_isspace(command[i]) == 0 && islimiter(command[i]) == 1 && ft_isquote(command[i]) == 0 &&command[i])
		{	
			if(wordfound == 1 && save != command[i])
				break;
			wordfound = 1;
			if (command[i] == '<')
			{
				if(command[i + 1] == '<')
				{
					type =  TOKEN_HEREDOC;
					i+= 2;
					break;
				}
				else		
					type = TOKEN_REDIR_IN;
				state = GENERAL;
			}
			if (command[i] == '>')
			{
				if(command[i + 1] == '>')
				{
					type = TOKEN_REDIR_APPEND;
					i += 2;
					break;
				}
				else
					type = TOKEN_REDIR_OUT;
				state = GENERAL;
			}
			else {
				type = getlimitertoken(command[i], command[i + 1]);
			}
			save = command[i];
			state = GENERAL;
			i++;
		}
		df = i;
		if(wordfound == 1)
			fill_node(tpos, df - tpos, command, cmd, &tnp, state, type);
		wordfound = 0;
	}
}
