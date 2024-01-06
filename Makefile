NAME= minishell
SOURCES= minishell.c syntaxerror.c parsing.c tools.c tools1.c
OBJECT= $(SOURCES:.c=.o)
CC = cc 
COMPFLAGS = -Wall -Wextra -Werror
LINKREADLINELIB = -lreadline

all: ${NAME}

${NAME}: ${OBJECT}
	$(CC) $(COMPFLAGS) -o $@ $^ $(LINKREADLINELIB)

%.o: %.c minishell.h
	$(CC) $(COMPFLAGS) -c $< -o $@

clean:
	rm -f ${OBJECT}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re