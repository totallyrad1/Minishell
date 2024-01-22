/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 14:11:54 by asnaji            #+#    #+#             */
/*   Updated: 2024/01/22 12:38:09 by asnaji           ###   ########.fr       */
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

enum e_type
{
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

typedef struct s_cmd
{
	char			*cmd;
	int				type;
	int				state;
	int				visited;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_tree
{
	char				*data;
	struct s_tree		*left;
	struct s_tree		*right;
	enum e_tree_type	tree_type;
}				t_tree;

//minishell.c
void	handle_input(t_cmd **cmd, char *str);
//syntaxerror.c
int		check_syntax_error(char *prompt);
int		brackets_check(char *command);
int		all_brackets(char *command, int count, int position);
//parsing.c
int		checkdelimiter(int c);
int		ft_bracket(t_cmd **cmd, char *command, int flag, int i);
//tools.c
size_t	ft_strlen(const char *s);
char	*ft_substr(char *s, size_t start, size_t len);
char	*ft_strdup(char *s1);
size_t	ft_strlen(const char *s);
void	ft_newnode(t_cmd **cmd, char *value);
void	ft_free_cmd(t_cmd *lst);
//parsing.c
int		ft_char(t_cmd **cmd, char *command, int flag, int i);
void	give_state_and_type(t_cmd **cmd);
//recursive_parsing1.c
int	getlimitertoken(char c, char f);
int	getlimitertoken1(char c, char f);
int	look_for_char(char *command, int i);
//recursive_parsing.c
int		ft_separator(t_cmd **cmd, char *command, int flag, int i);
int		ft_space(t_cmd **cmd, char *command, int flag, int i);
int		ft_quote(t_cmd **cmd, char *command, int flag, int i);
int		ft_switch(t_cmd **cmd, char *command, int flag, int i);
//tree.c
int		is_redirection(t_cmd *token);
t_tree	*make_node(t_cmd **cmd, int flag);
t_tree	*make_command(t_cmd *token);
t_tree	*search_pipe(t_cmd *token);
t_tree	*search_logical_operator(t_cmd *token);
//tree_utils2.c
t_cmd	*skip_brackets_next(t_cmd *token, int *is_brackets);
t_cmd	*skip_brackets_prev(t_cmd *token);
void	free_tree(t_tree **root);
//tree_utils.c
void	add_right_child(t_tree **node, t_cmd **token, int flag);
t_tree	*make_node(t_cmd **cmd, int flag);
t_tree	*check_token(t_cmd **token, int *flag);
void	join_data(t_tree *node, t_cmd **token);
//tools1.c
int		ft_isspace(char c);
int		ft_isquote(char c);
int		islimiter(int c);
//ft_split.c
char	**ft_split(char const *s, char c);
//pipetools.c
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char *s1, char *s2);
// ft_strtrim.c
char	*ft_strtrim(char const *s1, char const *set);
// free_array.c
void	ft_free_array(char **array);
// pwd.c
char	*get_pwd(char **envp);
// env.c
void	print_env(char **env);
// unset.c
char	**unset(char **envp, char *var);
//export.c
char	**ft_export(char **env, char *variable, int flag);
//cd.c 
char	**ft_cd(char *dir, char **env);
// signal.c
void	signal_handler(int signum);
// get_home_dir.c
char	*get_home_dir(char **envp);
// start_message.c
void	print_start_message(void);
//clone_env.c
char	**ft_clone_env(char **env);

void	print2D(t_tree *root);
#endif