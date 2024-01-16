/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 19:59:53 by asnaji            #+#    #+#             */
/*   Updated: 2024/01/16 00:44:13 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void fill_node(int start, int len, char *command, t_cmd **cmd, int *tnp)
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
	else if (c == '\'')
		return TOKEN_S_Q;
	else if (c == '<')
	{
		if(f == '<')
			return TOKEN_HEREDOC;
		return TOKEN_REDIR_IN;
	}
	else if (c == '>')
	{
		if(f == '>')
			return TOKEN_REDIR_APPEND;
		return TOKEN_REDIR_OUT;
	}
	else if (c == '|')
	{
		if(f == '|')
			return TOKEN_OR;
		return TOKEN_PIPE;
	}
	else if(c == '&' && f == '&')
	{
			return TOKEN_AND;
	}
	else if (c == '$')
		return TOKEN_DOLLAR;
	else if(c == '(')
		return TOKEN_OPEN_BRACKET;
	else if(c == ')')
		return TOKEN_CLOSED_BRACKET;
	return TOKEN_EXPR;
}

int look_for_char(char *command, int i)
{
	int flag = 0;
	while(command[i] && islimiter(command[i]) == 0)
	{
		if(ft_isspace(command[i]) == 0)
			flag = 1;
		i++;
	}
	return flag;
}

int ft_switch(t_cmd **cmd, char *command, int flag, int i)
{
	if(command[i])
	{
		if(ft_isspace(command[i]) == 1)
			return ft_space(cmd, command, flag, i);
		else if(ft_isquote(command[i]) == 1)
			return ft_quote(cmd, command, flag, i);
		else if(islimiter(command[i]) == 1)
			return ft_separator(cmd, command, flag, i);
		else if(command[i] == '(' || command[i] == ')')
			return ft_bracket(cmd, command, flag, i);
		else
		 	return ft_char(cmd, command, flag, i);
	}
	return 0;
}

int ft_char(t_cmd **cmd, char *command, int flag, int i)
{
	int	tmp;
	
	tmp = i;
	while(command[i] && islimiter(command[i]) == 0 && ft_isquote(command[i]) == 0 && ft_isspace(command[i]) == 0)
		i++;
	fill_node(tmp, i - tmp, command, cmd, &flag);
	return ft_switch(cmd, command, flag, i);
}

int ft_separator(t_cmd **cmd, char *command, int flag, int i)
{
	int	tmp;
	int	x;
	char	save;

	tmp = i;
	x = 0;
	save = command[i];
	while(command[i] && islimiter(command[i]) == 1 && ft_isquote(command[i]) == 0 && ft_isspace(command[i]) == 0 && x++ < 2 && save == command[i])
		i++;
	if(islimiter(command[i]) == 1 || look_for_char(command, i) == 0 || (command[tmp] == '&' && command[tmp + 1] != '&'))
	{
		printf("syntax error\n");
		return 1;
	}
	fill_node(tmp, i - tmp, command, cmd, &flag);
	return ft_switch(cmd, command, flag, i);
}

int ft_space(t_cmd **cmd, char *command, int flag, int i)
{
	int tmp;

	tmp = i;
	while(command[i] && islimiter(command[i]) == 0 && ft_isquote(command[i]) == 0 && ft_isspace(command[i]) == 1)
		i++;
	// fill_node(tmp, i - tmp, command, cmd, &flag);
	return ft_switch(cmd, command, flag, i);;
}

int ft_bracket(t_cmd **cmd, char *command, int flag, int i)
{
	int tmp;

	tmp = i;
	if(command[i] == '(' || command[i] == ')')
		i++;
	fill_node(tmp, i - tmp, command, cmd, &flag);
	return ft_switch(cmd, command, flag, i);
}

int ft_quote(t_cmd **cmd, char *command, int flag, int i)
{
	int tmp;
	char save;

	tmp = i;
	if(command[i] == '\'' || command[i] == '"')
		save = command[i++];
	while(command[i] && command[i] != save)
		i++;
	if(command[i] == '\'' || command[i] == '"')
	{
		fill_node(tmp, ++i - tmp, command, cmd, &flag);
		return ft_switch(cmd, command, flag, i);
	}
	else
	{
		printf("syntax error\n");
		return 1;
	}
	return 0;
}


//this function gives state and type depending on the first and second character
void give_state_and_type(t_cmd **cmd)
{
	t_cmd *curr;
	
	curr = *cmd;
	while(curr)
	{
		curr->type = getlimitertoken(curr->cmd[0], curr->cmd[1]);
		if(curr->cmd[0] == '"')
		{
			curr->state = IN_DQUOTE;
		}
		else if(curr->cmd[0] == '\'')
		{
			curr->state = IN_QUOTE;
		}
		else
			curr->state = GENERAL;
		curr = curr->next;
	}
}
