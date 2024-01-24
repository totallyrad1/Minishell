/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redapprend.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 23:29:14 by asnaji            #+#    #+#             */
/*   Updated: 2024/01/24 11:54:06 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		bread = read(fd, buffer, 99);
		if(bread == -1)
		{
			free(buffer);
			return ;
		}
		buffer[bread] = '\0';
		wholefile = ft_strjoin(wholefile, buffer);
	}
	free(buffer);
	fd1 = open(filetoappendto, O_CREAT | O_RDWR | O_APPEND, 0700);
	write(fd1, &wholefile, ft_strlen(wholefile));
}