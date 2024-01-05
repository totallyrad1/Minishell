NAME= minishell
SOURCES= minishell.c syntaxerror.c parsing.c tools.c
OBJECT= $(SOURCES:.c=.o)
CC = cc 
COMPFLAGS = -Wall -Wextra -Werror
LINKREADLINELIB = -lreadline



all : ${NAME}

${NAME} : ${OBJECT}
	$(CC) $(LINKREADLINELIB) $(COMPFLAGS) -o $@ $^

%.o : %.c minitalk.h
	$(CC) $(COMPFLAGS) $(LINKREADLINELIB) -c $< -o  $@

clean :
	rm -f ${OBJECT}

fclean : clean
	rm -f ${NAME}

re : fclean all

.PHONY : make clean fclean re 