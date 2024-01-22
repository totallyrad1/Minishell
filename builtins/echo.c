/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 22:17:48 by asnaji            #+#    #+#             */
/*   Updated: 2024/01/22 11:56:38 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(char *string, int flag)
{
	if (!string)
		return ;
	if (flag == 0)
		string = ft_strjoin(string, "\n");
	printf("%s", string);
}
