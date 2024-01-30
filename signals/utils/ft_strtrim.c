/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 17:52:58 by asnaji            #+#    #+#             */
/*   Updated: 2024/01/22 12:24:52 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	checkset(char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		else
			i++;
	}
	return (0);
}

static size_t	ft_trimstart(const char *s1, const char *set)
{
	size_t	i;

	i = 0;
	while (s1[i] && checkset(s1[i], set))
		i++;
	return (i);
}

static size_t	ft_trimend(const char *s1, const char *set)
{
	size_t	i;

	i = ft_strlen(s1);
	while (i > 0 && checkset(s1[i - 1], set))
		i--;
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmedstring;
	size_t	trimstart;
	size_t	trimend;
	size_t	len;
	size_t	i;

	trimstart = ft_trimstart(s1, set);
	trimend = ft_trimend(s1, set);
	len = (trimend - trimstart);
	i = 0;
	if (trimstart >= trimend)
		return (ft_strdup(""));
	trimmedstring = (char *)malloc((len + 1) * sizeof(char));
	if (trimmedstring == NULL)
		return (NULL);
	ft_strlcpy(trimmedstring, s1 + trimstart, len + 1);
	return (trimmedstring);
}
