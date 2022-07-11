PROJECT_NAME	= Philosophers
NAME			= philo
ACHIEV			= philo
SRC_d			= ./
SRC				= main.c philo.c philo_util.c tool.c
HEDER			= philo.h
SRC_o			= $(SRC:%.c=%.o)
CC				= cc
CFLAGS			= -Wall -Wextra -Werror

all : $(ACHIEV)

$(NAME) : $(ACHIEV)

$(ACHIEV) : $(SRC_d)$(HEDER) $(addprefix $(SRC_d),$(SRC_o))
	$(CC) $(addprefix $(SRC_d),$(SRC_o)) -o $(ACHIEV)

.c.o :
	$(CC) $(CFLAGS) -c $< -o $(basename $<).o

clean :
	rm -f $(addprefix $(SRC_d),$(SRC_o))

fclean : clean
	rm -f $(ACHIEV)

re : fclean all
