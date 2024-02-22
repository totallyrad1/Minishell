/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_matching_algorithm.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:33:29 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/22 22:51:34 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	init_data(t_pattern *data)
{
	data->i = 0;
	data->j = 0;
	data->last_asterisk = -1;
	data->match = 0;
}

static int	check(t_pattern *data, char *str, char *pattern)
{
	if (data->j < data->len_pattern && pattern[data->j] == str[data->i])
	{
		data->i++;
		data->j++;
	}
	else if (data->j < data->len_pattern && pattern[data->j] == '*')
	{
		data->last_asterisk = data->j;
		data->match = data->i;
		data->j++;
	}
	else if (data->last_asterisk != -1)
	{
		data->j = data->last_asterisk + 1;
		data->i = ++data->match;
	}
	else
		return (0);
	return (1);
}

int	is_match(char *str, char *pattern)
{
	t_pattern	data;

	data.len_pattern = ft_strlen(pattern);
	data.len_str = ft_strlen(str);
	init_data(&data);
	while (data.i < data.len_str)
	{
		if (check(&data, str, pattern))
			continue ;
		else
			return (0);
	}
	while (data.j < data.len_pattern && pattern[data.j] == '*')
		data.j++;
	return (data.j == data.len_pattern);
}
