NAME= minishell
SOURCES= ./builtins/cd.c ./builtins/echo.c ./builtins/exit.c ./builtins/export.c ./builtins/get_points.c ./builtins/print_env.c ./builtins/pwd.c ./builtins/unset.c ./env/add_env.c ./env/arr_to_env.c ./env/change_value.c ./env/del_node.c ./env/env_to_arr.c ./env/get_env_null.c ./env/get_node.c ./env/get_value.c ./env/key_exist.c ./env/make_env.c ./execution/here_doc.c ./execution/join_args.c ./execution/join_args1.c ./execution/join_args2.c ./execution/join_args3.c ./execution/join_args4.c ./execution/join_redir.c ./execution/onecommand.c ./execution/onecommandexec.c ./execution/pipeexecution.c ./execution/squote_or_dquote.c ./expand.c ./garbage_collector/rad_gc.c ./minishell.c ./parsing/parsing.c ./parsing/tree.c ./pipe.c ./signals/handle_signals.c ./syntaxerror.c ./utils/array_len.c ./utils/cmd_utils.c ./utils/fd_utils.c ./utils/ft_is.c ./utils/ft_is1.c ./utils/ft_isalpha.c ./utils/ft_itoa.c ./utils/ft_putstr.c ./utils/ft_split.c ./utils/ft_strchr.c ./utils/ft_strdup.c ./utils/ft_strjoin.c ./utils/ft_strlcpy.c ./utils/ft_strlen.c ./utils/ft_strncmp.c ./utils/ft_strtrim.c ./utils/ft_substr.c ./utils/recursive_parsing.c ./utils/recursive_parsing1.c ./utils/tools.c ./utils/tree_utils.c ./utils/tree_utils2.c ./wildcard/get_dirent.c ./wildcard/lst_utils.c ./wildcard/wildcard.c ./garbage_collector/fd_collector.c
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

#Compile Ubuntu
# ${NAME}: ${OBJECT}
# 	$(CC) -o $@ $^ -L $(LINKREADLINELIB) -lreadline

# %.o: %.c minishell.h
# 	$(CC) -c -I /usr/include $< -o $@

clean:
	@echo "Deleting object files ..."
	@rm -f ${OBJECT}

fclean:
	@echo "Deleting all ..."
	@rm -f ${NAME} ${OBJECT}

re: fclean all

.PHONY: all clean fclean re
