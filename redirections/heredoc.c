/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 11:51:12 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/09 09:36:20 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	heredoc(char *str)
{
	// int		fd;
	char	*text;
	// char *lktaba;

	// lktaba = NULL;
	// fd = open("hidden123456789", O_CREAT | O_RDWR, 0700);
	if (str && str[0])
	{
		while (420)
		{
			text = readline("> ");
			if (!text)
				break ;
			if (!ft_strcmp(text, str))
				break ;
			// else
				// lktaba = ft_strjoin(lktaba, text);
			free(text);
		}
		if (text)
			free(text);		
	}
	// write(1, lktaba, ft_strlen(lktaba));
	// free(lktaba);
	// return (fd);
	return (1);
}

int	ft_strlen_till_space(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != ' ' && (str[i] < 9 || str[i] > 13))
		i++;
	return (i);
}

void	exec_heredoc(char *str)
{
	char	*heredoc_index;
	char	*begin;
	char	*end_heredoc;

	heredoc_index = ft_strdup(str);
	begin = heredoc_index;
	heredoc_index = ft_strchr(heredoc_index, '<');
	while (heredoc_index)
	{
		if (*(++heredoc_index) == '<')
		{
			heredoc_index++;
			while (*(heredoc_index) == ' ' || (*heredoc_index >= 9 && *heredoc_index <= 13))
				heredoc_index++;
			end_heredoc = ft_strdup_len(heredoc_index, ft_strlen_till_space(heredoc_index));
			if (!end_heredoc)
				return ;
			heredoc(end_heredoc);
			free(end_heredoc);
		}
		else
			break ;
		heredoc_index = ft_strchr(heredoc_index, '<');
	}
	free(begin);
}
