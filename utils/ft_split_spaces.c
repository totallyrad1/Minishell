/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_spaces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:34:01 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/21 18:37:28 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#include "../minishell.h"

static size_t	wordscount(char const *s)
{
	size_t	i;
	size_t	wc;

	i = 0;
	wc = 0;
	while (s[i])
	{
		while (s[i] && ft_isspace(s[i]))
			i++;
		if (s[i])
			wc++;
		while (s[i] && ft_isspace(s[i]) == 0)
			i++;
	}
	return (wc);
}

static char	*getword(size_t *i, char const *s)
{
	size_t	j;
	size_t	currwordsize;
	size_t	tpos;
	char	*res;

	j = 0;
	while (s[*i] && ft_isspace(s[*i]))
		(*i)++;
	tpos = *i;
	while (s[*i] && ft_isspace(s[*i]) == 0)
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

char	**ft_split_spaces(char const *s)
{
	size_t	j;
	size_t	wc;
	size_t	i;
	char	**res;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	wc = wordscount(s);
	res = (char **)rad_malloc((wc + 1) * sizeof(char *), 0, OTHERS);
	while (j < wc)
	{
		res[j] = getword(&i, s);
		if (!res[j])
			return (NULL);
		j++;
	}
	res[j] = NULL;
	return (res);
}
