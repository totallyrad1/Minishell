NAME= minishell
SOURCES= minishell.c builtins/cd.c builtins/echo.c builtins/exit.c builtins/export.c builtins/print_env.c builtins/pwd.c builtins/unset.c builtins/utils_cd.c env/add_env.c env/arr_to_env.c env/change_value.c env/del_node.c env/env_to_arr.c env/get_env_null.c env/get_node.c env/get_value.c env/key_exist.c env/make_env.c execution/here_doc.c execution/join_args.c execution/join_args2.c execution/join_args3.c execution/join_args4.c execution/join_redir.c execution/onecommand.c execution/onecommandexec.c execution/pipeexecution.c execution/squote_or_dquote.c garbage_collector/fd_collector.c garbage_collector/rad_gc.c parsing/parsing.c parsing/tree.c signals/handle_signals.c utils/array_len.c utils/cmd_utils.c utils/fd_utils.c utils/fd_utils1.c utils/ft_is.c utils/ft_is1.c utils/ft_isalpha.c utils/ft_itoa.c utils/ft_putstr.c utils/ft_split.c utils/ft_split_spaces.c utils/ft_strchr.c utils/ft_strdup.c utils/ft_strjoin.c utils/ft_strlcpy.c utils/ft_strlen.c utils/ft_strncmp.c utils/ft_strtrim.c utils/ft_substr.c utils/join_hargs.c utils/pipe.c utils/recursive_parsing.c utils/recursive_parsing1.c utils/syntaxerror.c utils/syntaxerror1.c utils/tools.c utils/tools1.c utils/tree_utils.c utils/tree_utils2.c wildcard/get_dirent.c wildcard/lst_utils.c wildcard/pattern_matching_algorithm.c wildcard/utils_wildcard.c wildcard/wildcard.c env/sort_env.c
OBJECT= $(SOURCES:.c=.o)
CC = cc
COMPFLAGS = -Wall -Wextra -Werror -g
LINKREADLINELIB = $(shell brew --prefix readline)/lib
LINKREADLINELIB1 = $(shell brew --prefix readline)/include

all: ${NAME}

${NAME}: ${OBJECT}
	@echo "Compiling minishell ..."
	@$(CC) $(COMPFLAGS) -o $@ $^ -L $(LINKREADLINELIB) -lreadline

%.o: %.c minishell.h
	@echo "Compiling $< ..."
	@$(CC) $(COMPFLAGS) -c -I  $(LINKREADLINELIB1) $< -o $@ 

clean:
	@echo "Deleting object files ..."
	@rm -f ${OBJECT}

fclean:
	@echo "Deleting all ..."
	@rm -f ${NAME} ${OBJECT}

re: fclean all

.PHONY: all clean fclean re
