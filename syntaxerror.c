/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxerror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:57:36 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/21 16:29:44 by asnaji           ###   ########.fr       */
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

int check_limiterssyntax(t_token *curr, int initflag)
{
	if((islimiter1(curr->cmd[0]) && delimitercheck(curr->cmd) == 0) // valid delimiter
		|| (islimiter1(curr->cmd[0]) && !curr->next) // delimiter flkhr
		|| (islimiter2(curr->cmd[0]) && initflag == 0) // limiter flbdya 
		|| (islimiter2(curr->cmd[0]) && islimiter2(curr->next->cmd[0])) //delimiter mora delimier
		|| (isredirection(curr->cmd[0]) && isredirection(curr->next->cmd[0])) //redirection after reidr
		|| (isredirection(curr->cmd[0]) && islimiter1(curr->next->cmd[0])) // redirection moraha delimiter
		|| (islimiter1(curr->cmd[0]) && (curr->next->cmd[0] == ')')) // delimiter morah closed bracket
		|| (isredirection(curr->cmd[0]) && (curr->next->cmd[0] == ')' || curr->next->cmd[0] == '(')))  //redir moraha bracket
		{
			exitstatus(258, 1);
			return (printf("turboshell: parse error near `%s'\n", curr->cmd), 0);
		}
	return 1;
}

void init_vars(t_syntax **vars)
{
	*vars = rad_malloc(sizeof(t_syntax), 0, COMMAND);
	if(!*vars)
		ft_exit(NULL);
	(*vars)->closedc = 0;
	(*vars)->openc = 0;
	(*vars)->initflag = 0;
}

void set_flags(t_token *curr, t_syntax **vars)
{
	if(curr->type != TOKEN_CLOSED_BRACKET && curr->type != TOKEN_OPEN_BRACKET && curr->cmd &&  isredirection(curr->cmd[0]) == 0 && islimiter2(curr->cmd[0]) == 0)
			(*vars)->initflag = 1;
	if(curr->type == TOKEN_CLOSED_BRACKET)
		(*vars)->closedc++;	
	else if(curr->type == TOKEN_OPEN_BRACKET)
		(*vars)->openc++;
}

int check_bracketssyntax(t_token *curr, t_syntax *vars)
{
	if((vars->initflag == 0 && curr->cmd[0] == ')') // closed bracket flowl
		|| (isredirection(curr->cmd[0]) && curr->next && curr->next->cmd[0] == '(') //redirection moraha open bracket
		|| (curr->cmd[0] == ')' && curr->next && islimiter2(curr->next->cmd[0]) == 0) // closed bracket mn mora word
		|| (curr->cmd[0] == '(' && curr->next && islimiter2(curr->next->cmd[0])) // open bracket mn wraha limiter
		|| (curr->cmd[0] == '(' && curr->next && curr->next->cmd[0] == ')') // open bracket mn moraha closed bracket
		|| (islimiter2(curr->cmd[0]) == 0 && curr->next && curr->next->cmd[0] == '(')) //expression mn moraha bracket
		{
			exitstatus(258, 1);
			printf("turboshell: syntax error near unexpected token `%s'\n", curr->cmd);
			return (0);
		}
	return (1);
}

int check_syntax_error(t_token **cmd)
{
	t_token *curr;
	t_syntax *vars;

	curr = *cmd;
	init_vars(&vars);
	while(curr && heredocendedwith_c(0, 0) == 0)
	{
		set_flags(curr, &vars);
		if(check_limiterssyntax(curr, vars->initflag) == 0)
			return (0);
		if(check_bracketssyntax(curr, vars) == 0)
			return (0);
		if(delimitercheck(curr->cmd) == 1 &&curr->cmd && curr->cmd[0] == '<' && curr->cmd[1] == '<' && curr->cmd[2] == '\0' && curr->next && curr->next->cmd)
		{
			curr->heredocfd = heredocshit(curr->next->cmd);
			curr->for_heredoc = curr->next->for_heredoc; 
		}	
		curr = curr->next;
	}
	if(heredocendedwith_c(0, 0) == 1 && vars->openc != vars->closedc)
	{
		exitstatus(258, 1);
		return (printf("turboshell: syntax error near unexpected token `)'\n"), 0);
	}
	return (1);
}
