/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxerror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:57:36 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/13 21:55:37 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int delimitercheck(char *token)
{
	if(token[0] == '&' && token[1] == '&' && token[2] == '\0')
		return 1;
	if((token[0] == '|' && token[1] == '|' && token[2] == '\0' ) || (token[0] == '|' && token[1] == '\0'))
		return 1;
	if((token[0] == '<' && token[1] == '<' && token[2] == '\0') || (token[0] == '<' && token[1] == '\0'))
		return 1;
	if((token[0] == '>' && token[1] == '>' && token[2] == '\0') || (token[0] == '>' && token[1] == '\0'))
		return 1;
	return 0;
}



int check_syntax_error(t_token **cmd)
{
	t_token *curr;
	int initflag;
	int openc;
	int closedc;
	int flag;
	int flag1;
	int flag2;
	int flag3;

	curr = *cmd;
	closedc = 0;;
	openc = 0;
	flag = 0;
	flag1 = 0;
	flag2 = 0;
	flag3 = 0;
	initflag = 0;
	while(curr)
	{
		if(curr->cmd[0] == '<' && curr->cmd[1] == '<' && curr->cmd[2] == '\0' && curr->next && curr->next->cmd)
		{
			curr->heredocfd = heredocshit(curr->next->cmd);
			curr->for_heredoc = curr->next->for_heredoc; 
		}	
		if(curr->type != TOKEN_CLOSED_BRACKET && curr->type != TOKEN_OPEN_BRACKET && islimiter2(curr->cmd[0]) == 0)
			initflag = 1;
		if(curr->type == TOKEN_CLOSED_BRACKET)
		{
			closedc++;
			flag1 = 1;
			flag3 = 1;
		}		
		else if(curr->type == TOKEN_OPEN_BRACKET)
		{
			openc++;
			flag = 1;
		}
		if(curr->type != TOKEN_CLOSED_BRACKET && curr->type != TOKEN_OPEN_BRACKET && curr->type != TOKEN_EXPR && curr->type != TOKEN_DOLLAR)
		{
			flag2 = 0;
			flag1 = 0;
			flag3 = 0;
		}	
		if(curr->type == TOKEN_EXPR || curr->type == TOKEN_DOLLAR)
		{
			flag2 = 1;
			flag = 0;
		}
		if((islimiter1(curr->cmd[0]) == 1 && initflag == 0) 
			|| (islimiter1(curr->cmd[0]) == 1 && curr->next && islimiter1(curr->next->cmd[0]) == 1) 
			|| (curr->cmd[0] != '$' && islimiter(curr->cmd[0]) &&  !curr->next) 
			|| (islimiter1(curr->cmd[0]) && delimitercheck(curr->cmd) == 0) 
			|| (curr->cmd[0] == '>' && curr->next && curr->next->cmd[0] == '>')
			|| (curr->cmd[0] == '>' && curr->next && curr->next->cmd[0] == '<')
			|| (curr->cmd[0] == '<' && curr->next && curr->next->cmd[0] == '>')
			|| (curr->cmd[0] == '<' && curr->next && curr->next->cmd[0] == '>'))
			return (printf("turboshell: parse error near `%s'\n", curr->cmd), 0);
		if(closedc > openc || (flag == 1 && curr->type == TOKEN_CLOSED_BRACKET) 
			|| (flag1 == 1 && curr->type == TOKEN_OPEN_BRACKET) 
			|| (flag2 == 1 && curr->type == TOKEN_OPEN_BRACKET) 
			|| (flag3 == 1 && (curr->type == TOKEN_EXPR || curr->type == TOKEN_DOLLAR)))
			return (printf("turboshell: syntax error near unexpected token `%s'\n", curr->cmd),0);
		curr = curr->next;
	}
	if(openc != closedc)
		return (printf("turboshell: syntax error near unexpected token `)'\n"), 0);
	return 1;
}

// int bracketssyntax(t_token *cmd)
// {
// 	t_token *curr;
// 	int openc;
// 	int closedc;
// 	int flag;
// 	int flag1;
// 	int flag2;
// 	int flag3;

// 	curr = cmd;
// 	closedc = 0;;
// 	openc = 0;
// 	flag = 0;
// 	flag1 = 0;
// 	flag2 = 0;
// 	flag3 = 0;
// 	while(curr)
// 	{
// 		if(curr->type == TOKEN_CLOSED_BRACKET)
// 		{
// 			closedc++;
// 			flag1 = 1;
// 			flag3 = 1;
// 		}		
// 		else if(curr->type == TOKEN_OPEN_BRACKET)
// 		{
// 			openc++;
// 			flag = 1;
// 		}
// 		if(curr->type != TOKEN_CLOSED_BRACKET && curr->type != TOKEN_OPEN_BRACKET && curr->type != TOKEN_EXPR && curr->type != TOKEN_DOLLAR)
// 		{
// 			flag2 = 0;
// 			flag1 = 0;
// 			flag3 = 0;
// 		}	
// 		if(curr->type == TOKEN_EXPR || curr->type == TOKEN_DOLLAR)
// 		{
// 			flag2 = 1;
// 			flag = 0;
// 		}
// 		if(closedc > openc || (flag == 1 && curr->type == TOKEN_CLOSED_BRACKET) || (flag1 == 1 && curr->type == TOKEN_OPEN_BRACKET) || (flag2 == 1 && curr->type == TOKEN_OPEN_BRACKET) || (flag3 == 1 && (curr->type == TOKEN_EXPR || curr->type == TOKEN_DOLLAR)))
// 			return (printf("turboshell: syntax error near unexpected token `%s'\n", curr->cmd),0);
// 		curr = curr->next;
// 	}
// 	if(openc != closedc)
// 		return (printf("turboshell: syntax error near unexpected token `)'\n"), 0);
// 	return 1;
// }

