/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:17:14 by asnaji            #+#    #+#             */
/*   Updated: 2024/01/13 13:30:48 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(char *s1)
{
	char	*cpy;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s1[i])
		i++;
	cpy = (char *)malloc((i + 1) * sizeof(char));
	if (cpy == NULL)
		return (NULL);
	while (j < i)
	{
		cpy[j] = s1[j];
		j++;
	}
	cpy[j] = '\0';
	return (cpy);
}

char	*ft_substr(char *s, size_t start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	end;

	end = start + len;
	i = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	substr = (char *)malloc((len + 1) * sizeof(char));
	if (substr == NULL)
		return (0);
	while (i < len && s[start + i])
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

// void	ft_newnode(s_cmd **cmd, char *value, int type, int state)
// {
// 	s_cmd	*new_node;
// 	s_cmd	*curr;

// 	new_node = malloc(sizeof(s_cmd));
// 	if (!new_node)
// 		exit(0);
// 	curr = *cmd;
// 	new_node->next = NULL;
// 	new_node->cmd = value;
// 	new_node->state = state;
// 	new_node->type = type;
// 	while (curr->next)
// 		curr = curr->next;
// 	curr->next = new_node;
// }

void	ft_freeeverything(s_cmd *lst)
{
	s_cmd	*curr;
	s_cmd	*lastnode;

	if(!lst)
		return ;
	curr = lst;
	while (curr)
	{
		lastnode = curr;
		if (curr)
			curr = curr->next;
		else
		 	break;
		free(lastnode->cmd);
		free(lastnode);
	}
}
