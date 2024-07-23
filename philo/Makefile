NAME = philo

SRC = mandatory.c \
	  ft_errors.c \
	  ft_utils.c \
	  ft_init.c \
	  ft_action.c \
	  ft_pthread.c \
	  ft_monitor.c

OBJ = ${SRC:.c=.o}

CC = cc

CFLAGS = -Wall -Wextra -Werror -pthread -g

all : ${NAME}

${NAME} : ${OBJ}
	${CC} ${CFLAGS} ${OBJ} -o ${NAME}

clean :
	rm -f ${OBJ}

fclean : clean
	rm -f ${NAME}

re : fclean all

.PHONY : all fclean re
