/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirout.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 23:14:28 by asnaji            #+#    #+#             */
/*   Updated: 2024/01/23 23:59:28 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void redirout(int fd, char *filetowrite)
{
	int bread;
	char *wholefile;
	char *buffer;
	int fd1;

	bread = 1;
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
	free(buffer);
	fd1 = open(filetowrite, O_CREAT, O_RDWR, 0777);
	write(fd1, &wholefile, ft_strlen(wholefile));
}