/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:00:16 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/21 16:12:53 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	checkreadpermissions(char *str, int *infile)
{
	if (access(str, F_OK) == 0 && access(str, R_OK) != 0)
	{
		wrerror("bash: ");
		wrerror(str);
		wrerror(": Permission denied\n");
		*infile = -1;
		return (0);
	}
	return (1);
}

int	checkwritepermissions(char *str, int *outfile)
{
	if (access(str, F_OK) == 0 && access(str, W_OK) != 0)
	{
		wrerror("bash: ");
		wrerror(str);
		wrerror(": Permission denied\n");
		*outfile = -1;
		return (0);
	}
	return (1);
}

void	changeinfile(int fd)
{
	if (fd != 0)
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
}

void	changeoutfile(int fd)
{
	if (fd != 1)
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}
