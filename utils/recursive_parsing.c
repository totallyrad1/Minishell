/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:05:06 by asnaji            #+#    #+#             */
/*   Updated: 2024/01/30 16:40:34 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int hasspaceafter(char *str, int i)
{
	if(str[i + 1] == 32)
		return 1;
	return 0;
}

int	ft_char(t_token **cmd, char *command, int flag, int i)
{
	int	tmp;

	tmp = i;
	while (command[i] && islimiter(command[i]) == 0
		&& ft_isquote(command[i]) == 0 && ft_isspace(command[i]) == 0
		&& (command[i] != ')' && command[i] != '('))
		i++;
	if (flag == 1)
	{
		(*cmd)->cmd = ft_substr(command, tmp, i - tmp);
		(*cmd)->state = GENERAL;
		(*cmd)->spaceafter = hasspaceafter(command, i);
		flag = 0;
	}
	else
		ft_newnode(cmd, ft_substr(command, tmp, i - tmp), GENERAL, hasspaceafter(command, i));
	return (ft_switch(cmd, command, flag, i));
}

int	ft_separator(t_token **cmd, char *command, int flag, int i)
{
	int		tmp;
	int		x;
	char	save;

	tmp = i;
	x = 0;
	save = command[i];
	while (command[i] && islimiter(command[i]) == 1
		&& ft_isquote(command[i]) == 0
		&& ft_isspace(command[i]) == 0 && x++ < 2 && save == command[i])
		i++;
	if (islimiter(command[i]) == 1 || look_for_char(command, i) == 0
		|| (command[tmp] == '&' && command[tmp + 1] != '&'))
		return (printf("syntax error\n"), 1);
	if (flag == 1)
	{
		(*cmd)->cmd = ft_substr(command, tmp, i - tmp);
		(*cmd)->state = GENERAL;
		(*cmd)->spaceafter = hasspaceafter(command, i);
		flag = 0;
	}
	else
		ft_newnode(cmd, ft_substr(command, tmp, i - tmp), GENERAL, hasspaceafter(command, i));
	return (ft_switch(cmd, command, flag, i));
}

int	ft_space(t_token **cmd, char *command, int flag, int i)
{
	int	tmp;

	tmp = i;
	while (command[i] && islimiter(command[i]) == 0
		&& ft_isquote(command[i]) == 0 && ft_isspace(command[i]) == 1)
		i++;
	return (ft_switch(cmd, command, flag, i));
}

int	ft_bracket(t_token **cmd, char *command, int flag, int i)
{
	int	tmp;

	tmp = i;
	if (command[i] == '(' || command[i] == ')')
		i++;
	if (flag == 1)
	{
		(*cmd)->cmd = ft_substr(command, tmp, i - tmp);
		(*cmd)->state = GENERAL;
		(*cmd)->spaceafter = hasspaceafter(command, i);
		flag = 0;
	}
	else
		ft_newnode(cmd, ft_substr(command, tmp, i - tmp), GENERAL, hasspaceafter(command, i));
	return (ft_switch(cmd, command, flag, i));
}

int	ft_quote(t_token **cmd, char *command, int flag, int i)
{
	int		tmp;
	char	save;

	tmp = i + 1;
	if (command[i] == '\'' || command[i] == '"')
		save = command[i++];
	while (command[i] && command[i] != save)
		i++;
	if (command[i] == '\'' || command[i] == '"')
	{
		if (flag == 1)
		{
			(*cmd)->cmd = ft_substr(command, tmp, i - tmp);
			(*cmd)->spaceafter = hasspaceafter(command, i);
			if(save == '"')
				(*cmd)->state = IN_DQUOTE;
			else
			 	(*cmd)->state = IN_QUOTE;;
			flag = 0;
		}
		else
		{
			if(save == '"')
				ft_newnode(cmd, ft_substr(command, tmp, i - tmp), IN_DQUOTE, hasspaceafter(command, i));
			else
			 	ft_newnode(cmd, ft_substr(command, tmp, i - tmp), IN_QUOTE, hasspaceafter(command, i));
		}
		return (ft_switch(cmd, command, flag, ++i));
	}
	else
		return (printf("syntax error\n"), 1);
	return (0);
}
