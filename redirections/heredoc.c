/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 11:51:12 by asnaji            #+#    #+#             */
/*   Updated: 2024/01/24 12:09:34 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int heredoc(char *str)
{
	int fd;
	char *text;
	char *lktaba;

	fd = open("hidden123456789", O_CREAT | O_RDWR, 0700);
	lktaba = ft_strjoin(lktaba, str);
	while(ft_strncmp(text, str, 4) != 0)
	{
		text = readline(">");
		if(ft_strncmp(text, str, 4) != 0)
			lktaba = ft_strjoin(lktaba, text);
		free(text);
	}
	write(fd, lktaba, ft_strlen(lktaba));
	free(lktaba);
	return (fd);
}