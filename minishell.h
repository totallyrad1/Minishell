/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 14:11:54 by asnaji            #+#    #+#             */
/*   Updated: 2024/01/05 20:28:54 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
# include <curses.h>
# include <term.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct	t_cmd
{
	char *content;
	int type;
	int state;
	struct t_cmd	*next;
}				s_cmd;

enum e_type{
    TOKEN_EXPR,
    TOKEN_REDIR_IN,
    TOKEN_REDIR_OUT,
    TOKEN_REDIR_APPEND,
    TOKEN_HEREDOC,
    TOKEN_PIPE,
    TOKEN_SPACE,
    TOKEN_D_Q,
    TOKEN_S_Q,
    TOKEN_DOLLAR,
} ;

enum e_state
{
	GENERAL,
	IN_DQUOTE,
	IN_QUOTE,
};

//minishell.c
void handlenput(s_cmd **cmd, char *str);
//syntaxerror.c
int checksyntaxerror(char *prompt);
//parsing.c
int checkdelimiter(int c);
//tools.c
char	*ft_substr(char *s, size_t start, size_t len);
char	*ft_strdup(char *s1);
size_t	ft_strlen(char *s);
void	ft_newnode(s_cmd **cmd, char *value);
void	ft_freeeverything(s_cmd *lst);
//parsing.c
void tokenizer(s_cmd **cmd, char *command);

#endif