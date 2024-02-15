/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   squote_or_dquote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:33:31 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/15 18:25:50 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*quotes_toexpression(char *str, t_env *env)
{
	char	*new_str;
	char	*key;
	int		i;
	int		tmp;
	char	save;

	i = 0;
	save = str[i++];
	tmp = i;
	new_str = ft_strdup("");
	if (!new_str)
		return (NULL);
	while (str[i] && str[i] != save)
	{
		while (str[i] == '$'
			&& (ft_alphanum(str[i + 1]) == 1
				|| str[i + 1] == '?') && save != '\'')
		{
			new_str = ft_strjoin(new_str, ft_substr(str, tmp, i - tmp));
			i++;
			tmp = i;
			while (str[i] && (ft_alphanum(str[i]) == 1 || str[i] == '?'))
				i++;
			key = ft_substr(str, tmp, i - tmp);
			new_str = ft_strjoin(new_str, expand(env, key));
			tmp = i;
		}
		i++;
		if (str[i] == save)
			new_str = ft_strjoin(new_str, ft_substr(str, tmp, i - tmp));
	}
	return (new_str);
}

char	*heredoc_expanding(char *str, t_env *env)
{
	char	*new_str;
	char	*key;
	int		i;
	int		tmp;

	i = 0;
	tmp = i;
	new_str = ft_strdup("");
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		while (str[i] == '$'
			&& (ft_alphanum(str[i + 1]) == 1
				|| str[i + 1] == '?'))
		{
			new_str = ft_strjoin(new_str, ft_substr(str, tmp, i - tmp));
			i++;
			tmp = i;
			while (str[i] && (ft_alphanum(str[i]) == 1 || str[i] == '?'))
				i++;
			key = ft_substr(str, tmp, i - tmp);
			new_str = ft_strjoin(new_str, expand(env, key));
			tmp = i;
		}
		i++;
		if (str[i] == '\0')
			new_str = ft_strjoin(new_str, ft_substr(str, tmp, i - tmp));
	}
	return (new_str);
}
