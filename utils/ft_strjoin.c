/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:41:58 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/11 17:20:43 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*newstring;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1 || s1[0] == '\0')
		return (ft_strdup(s2));
	if (!s2)
		return (newstring = ft_strdup(s1), free(s1), newstring);
	newstring = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1));
	if (newstring == NULL)
		return (free(s1), NULL);
	while (s1[i])
	{
		newstring[i] = s1[i];
		i++;
	}
	while (s2[j])
		newstring[i++] = s2[j++];
	newstring[i] = '\0';
	return (free(s1), newstring);
}
