/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 20:17:16 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/21 18:36:49 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <sys/fcntl.h>
#include <unistd.h>

void	ft_readheredoc(int fd, char *delimiter)
{
	char	*str;
	char	*temp;

	while (1)
	{
		if (exitstatus(0, 0) == -1)
		{
			exitstatus(1, 1);
			break ;
		}
		str = readline("> ");
		temp = str;
		if (!str || ft_strcmp(str, delimiter) == 0)
		{
			free(str);
			break ;
		}
		str = ft_strjoin(ft_strdup(str), "\n");
		free(temp);
		write(fd, str, ft_strlen(str));
	}
}

int	heredocshit(char *delimiter)
{
	static int	hdcount;
	int			fd;
	int			fdtoreturn;
	char		*filename;

	hdcount += delimiter[0];
	exitstatus(0, 1);
	filename = ft_strjoin(ft_strdup(".heredoc"), ft_itoa(hdcount));
	fd = open(filename, O_CREAT | O_RDWR, 0644);
	fdtoreturn = open(filename, O_CREAT | O_RDWR, 0644);
	if (fd == -1 || fdtoreturn == -1)
		ft_exit(NULL);
	addfd(fd, 1);
	addfd(fdtoreturn, 1);
	unlink(filename);
	signal(SIGINT, (void (*)(int))signal_handler_heredoc);
	ft_readheredoc(fd, delimiter);
	signal(SIGINT, signal_handler);
	close(fd);
	return (fdtoreturn);
}

char	*heredocread(int fd)
{
	char	*everything;
	char	*buffer;
	int		bytes_read;

	buffer = rad_malloc(100, 0, COMMAND);
	everything = NULL;
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, 99);
		if (bytes_read == -1)
			ft_exit(NULL);
		buffer[bytes_read] = '\0';
		everything = ft_strjoin(everything, buffer);
	}
	return (everything);
}

int	heredoc_expanded(int fd, t_env *env)
{
	int		newfd;
	int		fdtoreturn;
	char	*everything;
	char	*new;

	everything = heredocread(fd);
	new = heredoc_expanding(everything, env);
	newfd = open(".hdexpanded999", O_CREAT | O_RDWR | O_TRUNC, 0644);
	fdtoreturn = open(".hdexpanded999", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (newfd == -1 || fdtoreturn == -1)
		ft_exit(NULL);
	addfd(newfd, 1);
	addfd(fdtoreturn, 1);
	write(newfd, new, ft_strlen(new));
	unlink(".hdexpanded999");
	close(newfd);
	return (fdtoreturn);
}
