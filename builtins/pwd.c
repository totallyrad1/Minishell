/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 15:27:22 by yzaazaa           #+#    #+#             */
/*   Updated: 2024/01/22 12:02:53 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_pwd(char **envp)
{
	char	*pwd1;

	pwd1 = (char *)malloc(5000);
	if (getcwd(pwd1, 5000) == NULL)
	{
		perror("getcwd");
		free(pwd1);
		return (NULL);
	}
	return (pwd1);
}
