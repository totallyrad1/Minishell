NAME= minishell
SOURCES= syntaxerror.c ./builtins/cd.c ./builtins/echo.c ./builtins/print_env.c ./builtins/export.c ./builtins/pwd.c ./builtins/unset.c ./minishell.c ./parsing/parsing.c ./parsing/tree.c ./pipe.c ./signals/handle_signals.c ./utils/clone_env.c ./utils/free_array.c ./utils/ft_is.c ./utils/ft_split.c ./utils/ft_strdup.c ./utils/ft_strjoin.c ./utils/ft_strlcpy.c ./utils/ft_strlen.c ./utils/ft_strncmp.c ./utils/ft_strtrim.c ./utils/ft_substr.c ./utils/recursive_parsing.c ./utils/recursive_parsing1.c ./utils/tools.c ./utils/tree_utils.c ./utils/tree_utils2.c ./utils/cmd_utils.c ./utils/ft_strchr.c ./execution/onecommand.c ./execution/pipeexecution.c ./env.c ./expand.c ./utils/ft_itoa.c ./utils/ft_isalpha.c ./execution/squote_or_dquote.c ./execution/join_args.c ./execution/join_args1.c ./execution/here_doc.c ./garbage_collector/rad_gc.c
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