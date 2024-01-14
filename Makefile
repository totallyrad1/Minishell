NAME= minishell
SOURCES= minishell.c syntaxerror.c pipe.c \
		utils/free_array.c utils/ft_is.c utils/ft_split.c utils/ft_strdup.c utils/ft_strjoin.c utils/ft_strlcpy.c \
		utils/ft_strlen.c utils/ft_strncmp.c utils/ft_strtrim.c utils/ft_substr.c utils/tools.c \
		signals/handle_signals.c \
		parsing/parsing.c \
		builtins/enc.v builtins/pwd.c builtins/unset.c
OBJECT= $(SOURCES:.c=.o)
CC = cc 
# COMPFLAGS = -Wall -Wextra -Werror
LINKREADLINELIB = -l[/goinfre/yzaazaa/.brew/Cellar/readline/8.2.7/include/readline]

all: ${NAME}

${NAME}: ${OBJECT}
	$(CC) -o $@ $^ $(LINKREADLINELIB)

%.o: %.c minishell.h
	$(CC) -c $< -o $@

clean:
	rm -f ${OBJECT}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re