/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 14:11:54 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/06 16:59:09 by yzaazaa          ###   ########.fr       */
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
# include <fcntl.h>
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


typedef struct s_token
{
	char			*cmd;
	int				type;
	int				state;
	int				visited;
	int				spaceafter;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

typedef struct s_cmd
{
	char			*cmd;
	int				fd[2];
	int				spaceafter;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_tree
{
	char				*data;
	int					fd[2];
	t_cmd				*next;
	struct s_tree		*left;
	struct s_tree		*right;
	enum e_tree_type	tree_type;
}				t_tree;

typedef struct s_env
{
	int				size;
	char			*key;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}				t_env;

typedef struct s_vars
{
	char			*cmd;
	int				flag;
	int				tmp;
	int				i;
	t_env			*env;
}				t_vars;

//minishell.c
void handle_input(t_token **cmd, char *str, t_env *env);
//syntaxerror.c
int		check_syntax_error(char *prompt);
int		brackets_check(char *command);
int		all_brackets(char *command, int count, int position);
//parsing.c
int		checkdelimiter(int c);
int		ft_bracket(t_token **cmd, t_vars *vars);
int		ft_dollarsign(t_token **cmd, t_vars *vars);
//tools.c
size_t	ft_strlen(const char *s);
char	*ft_substr(char *s, size_t start, size_t len);
char	*ft_strdup(char *s1);
char	*ft_strdup_len(char *s1, int len);
size_t	ft_strlen(const char *s);
void	ft_newnode(t_token **cmd, char *value, int state, int spaceafter);
void	ft_free_cmd(t_token *lst);
t_token	*init_token();
int		ft_isalpha(int c);
int		ft_isalnum(int c);

//parsing.c
int		ft_char(t_token **cmd, t_vars *vars);
void	give_state_and_type(t_token **cmd);
//recursive_parsing1.c
int		getlimitertoken(char c, char f);
int		getlimitertoken1(char c, char f);
int		look_for_char(char *command, int i);
//recursive_parsing3.c
t_token *join_args_ifspace(t_token *cmd);
//recursive_parsing.c
int		ft_separator(t_token **cmd, t_vars *vars);
int		ft_space(t_token **cmd, t_vars *vars);
int		ft_quote(t_token **cmd, t_vars *vars);
int		ft_switch(t_token **cmd, t_vars *vars);
int 	hasspaceafter(char *str, int i);
//tree.c
t_tree	*make_node(t_token **cmd, int flag);
t_tree	*make_command(t_token *token);
t_tree	*search_pipe(t_token *token);
t_tree	*search_logical_operator(t_token *token);
//tree_utils2.c
t_token	*skip_brackets_next(t_token *token, int *is_brackets);
t_token	*skip_brackets_prev(t_token *token);
void	free_tree(t_tree **root);
//tree_utils.c
t_tree	*make_node(t_token **cmd, int flag);
t_tree	*check_token(t_token **token, int *flag);
void	join_data(t_cmd *cmd, t_token **token);
//cmd_utils.c
t_cmd	*make_cmd(t_token *token);
void	add_cmd(t_cmd **cmd, t_token *token);
//tools1.c
int		ft_isspace(char c);
int		ft_isquote(char c);
int		ft_alphanum(char c);
int		islimiter(int c);
//ft_split.c
char	**ft_split(char const *s, char c);
//pipetools.c
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strjoin(char *s1, char *s2);
//pipe.c
char *get_working_path(char **envp, char *command);
char *get_path_line(char **envp);
void ft_pipe(char **av, char **envp, char *command, char *command2, char **commandargs1, char **commandargs2);
// ft_strtrim.c
char	*ft_strtrim(char const *s1, char const *set);
// ft_strncmp.c
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
// ft_strchr.c
char	*ft_strchr(const char *str, int c);
// free_array.c
void	ft_free_array(char **array);
// pwd.c
char	*get_pwd(t_env **envp);
// print_env.c
void	print_env(t_env *env);
// env.c
t_env	*arr_to_env(char **env);
void	add_env(t_env **env, char *key, char *value);
char	**env_to_arr(t_env *env);
// expand.c
char	*expand(t_env *env, char *key);
// unset.c
int	unset(char **args, t_env **envp);
//export.c
int		ft_export(char **args, t_env **env);
//cd.c 
int		ft_cd(char **args, t_env **env);
//echo.c
int		ft_echo(char **args);
// signal.c
void	signal_handler(int signum);
// start_message.c
void	print_start_message(void);
// clone_env.c
char	**ft_clone_env(char **env);
// heredoc.c
int		heredoc(char *str);
void	exec_heredoc(char *str);
//onecommand.c
void	find_node_to_execute(t_tree *root, t_env *env);
int	one_command_execution(t_tree *node, t_env *env);
int  andorexecution(t_tree *root, t_env *env);
//pipeexecution.c
int	pipe_execution(t_tree *node, t_env *env);
int pipeexecution1(t_tree *node, t_tree *save, t_env *env);
//expand.c
char	*expand(t_env *env, char *key);

int improvedpipeexecution(t_tree *node, t_env *env);
int exitstatus(int nestatus, int flag);
//ft_itoa.c
char	*ft_itoa(int n);
void	print2D(t_tree *root);
#endif