NAME = philo
DIR = srcs/
FILES = main.c \
		argument_set.c \
		check.c \
		monitor.c \
		philo_display.c \
		philo_eat.c \
		philo_operation.c \
		philo_put.c \
		philo_satisfied.c \
		philo_start_sleep.c \
		philo_stop.c \
		philo_take_fork.c \
		philo_utils.c \
		philo.c \
		create_utils.c \
		utils/utils.c \


SRCS = ${addprefix ${DIR},${FILES}}

CC = gcc

CFLAGS = -Wall -Wextra -Werror

OBJS = ${SRCS:.c=.o}

INC = -Iincludes
 
.c.o:
	${CC} ${CFLAGS} ${INC} -c $< -o ${<:.c=.o}

all: ${NAME}

$(NAME): ${OBJS}
	${CC} -pthread ${OBJS} -o ${NAME} 


clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
