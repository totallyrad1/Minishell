/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 14:11:54 by asnaji            #+#    #+#             */
/*   Updated: 2024/01/19 17:17:41 by yzaazaa          ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/wait.h>
// # include "readline/readline.h"
// # include "readline/history.h>

enum e_type{
    TOKEN_EXPR,
    TOKEN_REDIR_IN,
    TOKEN_REDIR_OUT,
    TOKEN_REDIR_APPEND,
    TOKEN_HEREDOC,
    TOKEN_PIPE,
    TOKEN_AND,
    TOKEN_OR,
    TOKEN_SPACE,
    TOKEN_D_Q,
    TOKEN_S_Q,
    TOKEN_DOLLAR,
	TOKEN_OPEN_BRACKET,
	TOKEN_CLOSED_BRACKET,
} ;

enum e_state
{
	GENERAL,
	IN_DQUOTE,
	IN_QUOTE,
};

enum e_tree_type
{
	AND,
	OR,
	PIPE,
	CMD,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	REDIR_APPEND,
};

typedef struct	s_cmd
{
	char *cmd;
	int type;
	int state;
	int	visited;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_tree
{
	char	*data;
	struct s_tree	*left;
	struct s_tree	*right;
	enum e_tree_type	tree_type;
}			t_tree;

// typedef struct s_redirection_elem
// {
// 	char						*arg;
// 	enum e_type					type;
// 	struct s_redirection_elem	*next;
// }				t_redirection_elem;

// typedef struct s_redirection_list
// {
// 	t_redirection_elem	*head;
// 	t_redirection_elem	*tail;
// 	int					size;
// }				t_redirection_list;

// typedef struct s_cmd_toexec
// {
// 	char	            **cmd;
// 	int		            fd_in;
// 	int		            fd_out;
// 	t_redirection_list  *redirection_list;
// }	t_cmd_toexec;

//minishell.c
void handle_input(t_cmd **cmd, char *str);
//syntaxerror.c
int check_syntax_error(char *prompt);
int brackets_check(char *command);
int all_brackets(char *command, int count, int position);
//parsing.c
int checkdelimiter(int c);
int ft_bracket(t_cmd **cmd, char *command, int flag, int i);
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
int ft_switch(t_cmd **cmd, char *command, int flag, int i);
void give_state_and_type(t_cmd **cmd);
//tree.c
t_tree *make_node(t_cmd **cmd, int flag);
t_tree *make_command(t_cmd *token);
t_tree *search_pipe(t_cmd *token);
t_tree *search_logical_operator(t_cmd *token);
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
//export.c
char **ft_export(char **env, char *variable, int flag);
//cd.c 
char **ft_cd(char *dir, char **env);
// signal.c
void	signal_handler(int signum);
// get_home_dir.c
char	*get_home_dir(char **envp);
// start_message.c
void    print_start_message(void);

void print2D(t_tree* root);
#endif