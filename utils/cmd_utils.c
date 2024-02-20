/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 05:32:03 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/02/20 23:56:07 by yzaazaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*make_cmd(t_token *token)
{
	t_cmd	*cmd;

	cmd = rad_malloc(sizeof(t_cmd), 0, COMMAND);
	if (!cmd)
		ft_exit(NULL);
	cmd->cmd = ft_strdup(token->cmd);
	cmd->fd[0] = -1;
	cmd->fd[1] = -1;
	cmd->next = NULL;
	cmd->heredocfd = token->heredocfd;
	cmd->expandheredoc = token->for_heredoc;
	cmd->spaceafter = token->spaceafter;
	return (cmd);
}

void	add_cmd(t_cmd **cmd, t_token *token)
{
	t_cmd	*new;
	t_cmd	*tmp;

	new = make_cmd(token);
	tmp = *cmd;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
