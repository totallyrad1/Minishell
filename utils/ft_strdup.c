/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:40:31 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/21 18:37:51 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup(char *s1)
{
	char	*cpy;
	int		i;
	int		j;

	if (!s1)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		i++;
	cpy = rad_malloc(i + 1, 0, OTHERS);
	while (j < i)
	{
		cpy[j] = s1[j];
		j++;
	}
	cpy[j] = '\0';
	return (cpy);
}

char	*ft_strdup_len(char *s1, int len)
{
	char	*cpy;
	int		i;

	if (!s1)
		return (NULL);
	i = 0;
	cpy = rad_malloc(len + 1, 0, OTHERS);
	while (i < len)
	{
		cpy[i] = s1[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

char	*ft_strdup_del(char *s1)
{
	int		i;
	int		j;
	char	*cpy;

	if (!s1)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		i++;
	cpy = rad_malloc(i + 1, 0, OTHERS);
	while (j < i)
	{
		cpy[j] = s1[j];
		j++;
	}
	cpy[j] = '\0';
	free(s1);
	return (cpy);
}
