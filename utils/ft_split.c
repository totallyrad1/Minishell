/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 17:44:50 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/21 18:37:34 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	wordscount(char const *s, char c)
{
	size_t	i;
	size_t	wc;

	i = 0;
	wc = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			wc++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (wc);
}

static char	*getword(size_t *i, char const *s, char c)
{
	size_t	j;
	size_t	currwordsize;
	size_t	tpos;
	char	*res;

	j = 0;
	while (s[*i] && s[*i] == c)
		(*i)++;
	tpos = *i;
	while (s[*i] && s[*i] != c)
		(*i)++;
	currwordsize = *i - tpos;
	res = (char *)rad_malloc((currwordsize + 1) * sizeof(char), 0, OTHERS);
	while (tpos + j < *i)
	{
		res[j] = s[tpos + j];
		j++;
	}
	res[j] = '\0';
	return (res);
}

char	**ft_split(char const *s, char c)
{
	size_t	j;
	size_t	wc;
	size_t	i;
	char	**res;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	wc = wordscount(s, c);
	res = (char **)rad_malloc((wc + 1) * sizeof(char *), 0, OTHERS);
	while (j < wc)
	{
		res[j] = getword(&i, s, c);
		if (!res[j])
			return (NULL);
		j++;
	}
	res[j] = NULL;
	return (res);
}
