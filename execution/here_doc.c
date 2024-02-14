/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 20:17:16 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/14 08:42:49 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <sys/fcntl.h>
#include <unistd.h>

void ft_readheredoc(int fd, char *delimiter)
{
	char *str;

	while(1)
	{
		str = readline(">");
		if(!str || ft_strcmp(str, delimiter) == 0)
			break;
		str = ft_strjoin(str, "\n");
		write(fd, str, ft_strlen(str));
		free(str);
	}
}

int heredocshit(char *delimiter)
{
	static int	hdcount;
	int			fd;
	int			fdtoreturn;
	char		*filename;

	hdcount++;
	filename = ft_strjoin(ft_strdup(".heredoc"), ft_itoa(hdcount));
	fd = open(filename, O_CREAT | O_RDWR, 0644);
	fdtoreturn = open(filename, O_CREAT | O_RDWR, 0644);
	unlink(filename);
	free(filename);
	ft_readheredoc(fd, delimiter);
	close(fd);
	return (fdtoreturn);
}

int heredoc_expanded(int fd, t_env *env)
{
	char	*buffer;
	int		newfd;
	int		fdtoreturn;
	char	*everything;
	int		bytes_read;
	char	*new;
	
	buffer = malloc(100);
	everything = NULL;
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, 99);
		if(bytes_read == -1)
			return (free(buffer), -1);
		buffer[bytes_read] = '\0';
		everything = ft_strjoin(everything, buffer);
	}
	new = heredoc_expanding(everything, env);
	newfd = open("dasdasdas", O_CREAT | O_RDWR | O_TRUNC, 0644);
	fdtoreturn = open("dasdasdas", O_CREAT | O_RDWR | O_TRUNC, 0644);
	write(newfd, new, ft_strlen(new));
	unlink("dasdasdas");
	close(newfd);
	return (free(buffer), free(everything),fdtoreturn);
}
