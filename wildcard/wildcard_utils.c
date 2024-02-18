/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 22:30:30 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/18 16:41:01 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_before_wildcard(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '*' && str[i] != '\n')
		i++;
	return (ft_strdup_len(str, i));
}

char	*get_after_wildcard(char *str)
{
	if (!str)
		return (NULL);
	while (*str && *str != '*' && *str != '\n')
		str++;
	if (*str == '*')
		str++;
	return (ft_strdup(str));
}

char	**ret_same(char *str)
{
	char	**ret;

	ret = rad_malloc(sizeof(char *) * 2, 0, COMMAND);
	if (!ret)
		return (NULL);
	ret[0] = ft_strdup(str);
	ret[1] = NULL;
	return (ret);
}
