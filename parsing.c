/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 19:59:53 by asnaji            #+#    #+#             */
/*   Updated: 2024/01/13 13:08:20 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void fill_node(int start, int len, char *command, s_cmd **cmd, int *tnp)
{
	if(*tnp == 1)
	{
		(*cmd)->cmd = ft_substr(command, start, len);
		*tnp = 0;
	}
	else
	 	ft_newnode(cmd, ft_substr(command, start, len));
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
	return -1;
}

// void tokenizer(s_cmd **cmd, char *command)
// {
// 	int tpos = 0;
// 	int df = 0;
// 	int i = 0;;
// 	int tnp = 1;
// 	char save;
// 	int wordfound = 0;
// 	int type = 0;
// 	int state = 0;
	
// 	while(command[i])
// 	{
// 		tpos = i;
// 		while(ft_isspace(command[i]) == 0 && islimiter(command[i]) == 0 && ft_isquote(command[i]) == 0 &&command[i])
// 		{	
// 			wordfound = 1;
// 			i++;
// 			type = TOKEN_EXPR;
// 			state = GENERAL;
// 		}
// 		df = i;
// 		if(wordfound == 1)
// 			fill_node(tpos, df - tpos, command, cmd, &tnp, state , type);
// 		wordfound = 0;
// 		tpos = i;
// 		while(ft_isspace(command[i]) == 1 && islimiter(command[i]) == 0 && ft_isquote(command[i]) == 0 &&command[i])
// 		{	
// 			wordfound = 1;
// 			i++;
// 			type = TOKEN_SPACE;
// 			state = GENERAL;
// 		}
// 		df = i;
// 		if(wordfound == 1)
// 			fill_node(tpos, df - tpos, command, cmd, &tnp, state, type);
// 		wordfound = 0;
// 		if(ft_isquote(command[i]) == 1)
// 		{
// 			tpos = i;
// 			save = command[i++];
// 			df = i;
// 			if(save == '\'')
// 			{
// 				state = GENERAL;
// 				type = TOKEN_S_Q;
// 			}
// 			else if(save == '"')
// 			{
// 				state = GENERAL;
// 				type = TOKEN_D_Q;
// 			}
// 			fill_node(tpos, df - tpos, command, cmd, &tnp, state, type);
// 			tpos = i;
// 			while(command[i] != save && command[i])
// 			{
// 				i++;
// 				wordfound = 1;
// 				if(save == '\'')
// 				{
// 					state = IN_QUOTE;
// 					type = TOKEN_EXPR;
// 				}
// 				else if(save == '"')
// 				{
// 					state = IN_DQUOTE;
// 					type = TOKEN_EXPR;
// 				}
// 			}
// 			df = i;
// 			if(wordfound == 1)
// 				fill_node(tpos, df - tpos, command, cmd, &tnp, state, type);
// 			wordfound = 0;
// 			tpos = i;
// 			i++;
// 			df = i;
// 			if(save == '\'')
// 			{
// 				state = GENERAL;
// 				type = TOKEN_S_Q;
// 			}
// 			else if(save == '"')
// 			{
// 				state = GENERAL;
// 				type = TOKEN_D_Q;
// 			}
// 			fill_node(tpos, df - tpos, command, cmd, &tnp, state, type);
// 		}
// 		tpos = i;
// 		while(ft_isspace(command[i]) == 0 && islimiter(command[i]) == 1 && ft_isquote(command[i]) == 0 &&command[i])
// 		{	
// 			if(wordfound == 1 && save != command[i])
// 				break;
// 			wordfound = 1;
// 			if (command[i] == '<')
// 			{
// 				if(command[i + 1] == '<')
// 				{
// 					type =  TOKEN_HEREDOC;
// 					i+= 2;
// 					break;
// 				}
// 				else		
// 					type = TOKEN_REDIR_IN;
// 				state = GENERAL;
// 			}
// 			if (command[i] == '>')
// 			{
// 				if(command[i + 1] == '>')
// 				{
// 					type = TOKEN_REDIR_APPEND;
// 					i += 2;
// 					break;
// 				}
// 				else
// 					type = TOKEN_REDIR_OUT;
// 				state = GENERAL;
// 			}
// 			else {
// 				type = getlimitertoken(command[i], command[i + 1]);
// 			}
// 			save = command[i];
// 			state = GENERAL;
// 			i++;
// 		}
// 		df = i;
// 		if(wordfound == 1)
// 			fill_node(tpos, df - tpos, command, cmd, &tnp, state, type);
// 		wordfound = 0;
// 	}
// }


int ft_char(s_cmd **cmd, char *command, int flag, int i)
{
	int	tmp;
	
	tmp = i;
	while(command[i] && islimiter(command[i]) == 0 && ft_isquote(command[i]) == 0 && ft_isspace(command[i]) == 0)
		i++;
	fill_node(tmp, i - tmp, command, cmd, &flag);
	if(islimiter(command[i]) == 1)
		ft_separator(cmd, command, flag, i);
	if(ft_isspace(command[i]) == 1)
		ft_space(cmd, command, flag, i);
	return 0;
}

int ft_separator(s_cmd **cmd, char *command, int flag, int i)
{
	int tmp;

	tmp = i;
	while(command[i] && islimiter(command[i]) == 1 && ft_isquote(command[i]) == 0 && ft_isspace(command[i]) == 0)
		i++;
	fill_node(tmp, i - tmp, command, cmd, &flag);
	if(ft_isspace(command[i]) == 1)
		ft_space(cmd, command, flag, i);
	if(command[i])
		ft_char(cmd, command, flag, i);
	return 0;
}

int ft_space(s_cmd **cmd, char *command, int flag, int i)
{
	int tmp;

	tmp = i;
	while(command[i] && islimiter(command[i]) == 0 && ft_isquote(command[i]) == 0 && ft_isspace(command[i]) == 1)
		i++;
	fill_node(tmp, i - tmp, command, cmd, &flag);
	if(islimiter(command[i]) == 1)
		ft_separator(cmd, command, flag, i);
	if(command[i])
		ft_char(cmd, command, flag, i);
	return 0;
}

