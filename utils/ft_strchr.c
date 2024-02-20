/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 03:05:05 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/20 23:57:58 by yzaazaa          ###   ########.fr       */
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
