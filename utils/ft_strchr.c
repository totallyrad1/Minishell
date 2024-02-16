/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 03:05:05 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/16 19:29:40 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != (char)c)
		i++;
	if (str && str[i] == (char)c)
		return ((char *)str + i);
	else
		return (NULL);
}