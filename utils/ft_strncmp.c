/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:42:18 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/21 00:01:03 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (i < n && (s2[i] || s1[i]))
	{
		if ((unsigned char)s1[i] == (unsigned char)s2[i])
			i++;
		else
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_strncmp_rev(const char *s1, const char *s2, size_t n)
{
	int	len_s1;
	int	len_s2;

	if (!s1 || !s2)
		return (0);
	len_s1 = 0;
	len_s2 = 0;
	while (s1[len_s1])
		len_s1++;
	while (s2[len_s2])
		len_s2++;
	len_s1--;
	len_s2--;
	while (n && len_s1 >= 0 && len_s2 >= 0)
	{
		if ((unsigned char)s1[len_s1] != (unsigned char)s2[len_s2])
			return ((unsigned char)s1[len_s1] - (unsigned char)s2[len_s2]);
		len_s1--;
		len_s2--;
		n--;
	}
	return (0);
}
