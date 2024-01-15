NAME= minishell
SOURCES= ./start_message.c ./builtins/cd.c ./builtins/echo.c ./builtins/env.c ./builtins/export.c ./builtins/get_home_dir.c ./builtins/pwd.c ./builtins/unset.c ./minishell.c ./parsing/parsing.c ./pipe.c ./signals/handle_signals.c ./syntaxerror.c ./utils/free_array.c ./utils/ft_is.c ./utils/ft_split.c ./utils/ft_strdup.c ./utils/ft_strjoin.c ./utils/ft_strlcpy.c ./utils/ft_strlen.c ./utils/ft_strncmp.c ./utils/ft_strtrim.c ./utils/ft_substr.c ./utils/tools.c
OBJECT= $(SOURCES:.c=.o)
CC = cc 
# COMPFLAGS = -Wall -Wextra -Werror
LINKREADLINELIB = $(shell brew --prefix readline)/lib
LINKREADLINELIB1 = $(shell brew --prefix readline)/include

all: ${NAME}

#Compile MacOS
# ${NAME}: ${OBJECT}
# 	$(CC) -o $@ $^ -L $(LINKREADLINELIB) -lreadline

# %.o: %.c minishell.h
# 	$(CC) -c -I $(LINKREADLINELIB1) $< -o $@ 

#Compile Ubuntu
${NAME}: ${OBJECT}
	$(CC) -o $@ $^ -L $(LINKREADLINELIB) -lreadline

%.o: %.c minishell.h
	$(CC) -c -I /usr/include $< -o $@

clean:
	rm -f ${OBJECT}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re