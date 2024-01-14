/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 22:17:48 by asnaji            #+#    #+#             */
/*   Updated: 2024/01/14 22:18:43 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(char *string, int flag)
{
	int i = 0;
	if (!string)
		return ;
	if (flag == 0)
		string = ft_strjoin(string, "\n");
	printf("%s", string + i);
}