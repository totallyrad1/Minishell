/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redapprend.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 23:29:14 by asnaji            #+#    #+#             */
/*   Updated: 2024/01/23 23:56:30 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <sys/fcntl.h>

void redirappend(int fd, char *filetoappendto)
{
	int fd1;
	int bread;
	char *buffer;
	char *wholefile;
	
	buffer = malloc(100);
	if(!buffer)
		return ;
	while(bread > 0)
	{
		bread = read(fd, buffer, 100);
		if(bread == -1)
		{
			free(buffer);
			return ;
		}
		buffer[bread] = '\0';
		wholefile = ft_strjoin(wholefile, buffer);
	}
	fd1 = open(filetoappendto, O_CREAT | O_RDWR, 0777);
	bread = 1;
	while(bread > 0)
	{
		bread = read(fd, buffer, 100);
		if(bread == -1)
		{
			free(buffer);
			return ;
		}
		buffer[bread] = '\0';
	}
	free(buffer);
	write(fd1, &wholefile, ft_strlen(wholefile));
}