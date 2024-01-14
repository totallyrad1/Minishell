/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 14:11:54 by asnaji            #+#    #+#             */
/*   Updated: 2024/01/14 22:50:15 by asnaji           ###   ########.fr       */
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
# include <unistd.h>
# include <signal.h>
// # include "readline/readline.h"
// # include "readline/history.h>

typedef struct	s_cmd
{
	char *cmd;
	char **args;
	int type;
	int state;
	struct s_cmd	*next;
}				t_cmd;

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
void handle_input(t_cmd **cmd, char *str);
//syntaxerror.c
int check_syntax_error(char *prompt);
//parsing.c
int checkdelimiter(int c);
//tools.c
size_t	ft_strlen(const char *s);
char	*ft_substr(char *s, size_t start, size_t len);
char	*ft_strdup(char *s1);
size_t	ft_strlen(const char *s);
void	ft_newnode(t_cmd **cmd, char *value);
void	ft_free_cmd(t_cmd *lst);
//parsing.c
void fill_node(int start, int len, char *command, t_cmd **cmd, int *tnp);
int ft_char(t_cmd **cmd, char *command, int flag, int i);
int ft_separator(t_cmd **cmd, char *command, int flag, int i);
int ft_space(t_cmd **cmd, char *command, int flag, int i);
int ft_quote(t_cmd **cmd, char *command, int flag, int i);
void ft_switch(t_cmd **cmd, char *command, int flag, int i);
//tools1.c
int ft_isspace(char c);
int ft_isquote(char c);
int islimiter(int c);
//ft_split.c
char	**ft_split(char const *s, char c);
//pipetools.c
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char *s1, char *s2);
// ft_strtrim.c
char	*ft_strtrim(char const *s1, char const *set);
// free_array.c
void	ft_free_array(char **array);
// pwd.c
char	*get_pwd(char **envp);
// env.c
void    print_env(char **env);
// unset.c
char	**unset(char **envp, char *var);
// signal.c
void	signal_handler(int signum);
// get_home_dir.c
char	*get_home_dir(char **envp);

#endif