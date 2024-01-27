NAME= minishell
SOURCES= ./builtins/cd.c ./builtins/echo.c ./builtins/env.c ./builtins/export.c ./builtins/get_home_dir.c ./builtins/pwd.c ./builtins/unset.c ./minishell.c ./parsing/parsing.c ./parsing/tree.c ./pipe.c ./signals/handle_signals.c ./utils/clone_env.c ./utils/free_array.c ./utils/ft_is.c ./utils/ft_split.c ./utils/ft_strdup.c ./utils/ft_strjoin.c ./utils/ft_strlcpy.c ./utils/ft_strlen.c ./utils/ft_strncmp.c ./utils/ft_strtrim.c ./utils/ft_substr.c ./utils/recursive_parsing.c ./utils/recursive_parsing1.c ./utils/syntaxerror.c ./utils/tools.c ./utils/tree_utils.c ./utils/tree_utils2.c ./utils/cmd_utils.c ./redirections/heredoc.c ./utils/ft_strchr.c
OBJECT= $(SOURCES:.c=.o)
CC = cc 
# COMPFLAGS = -Wall -Wextra -Werror -g
LINKREADLINELIB = $(shell brew --prefix readline)/lib
LINKREADLINELIB1 = $(shell brew --prefix readline)/include

all: ${NAME}

${NAME}: ${OBJECT}
	@echo "Compiling minishell ..."
	@$(CC) -g -o $@ $^ -L $(LINKREADLINELIB) -lreadline

%.o: %.c minishell.h
	@echo "Compiling $< ..."
	@$(CC) -g -c -I  $(LINKREADLINELIB1) $< -o $@ 

# #Compile Ubuntu
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