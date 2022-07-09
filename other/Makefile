PROJECT_NAME	= Philosophers
NAME			= philo
ACHIEV			= philo
ACHIEVb			= $(ACHIEV)_bonus
SRC_d			= src/
SRCb_d			= src_bonus/
SRC				= itou.c  main.c
SRCb			= 
HEDER			= philo.h
HEDERb			= 
SRC_o			= $(SRC:%.c=%.o)
SRCb_o			= $(SRCb:%.c=%.o)
CC				= cc
CFLAGS			= -Wall -Wextra -Werror

all : $(ACHIEV)

$(NAME) : $(ACHIEV)

bonus : $(ACHIEVb)

$(ACHIEV) : $(SRC_d)$(HEDER) $(addprefix $(SRC_d),$(SRC_o))
	$(CC) $(addprefix $(SRC_d),$(SRC_o)) -o $(ACHIEV)

$(ACHIEVb) : $(SRCb_d)$(HEDERb) $(addprefix $(SRCb_d),$(SRCb_o)) $(MINLIBX)
	$(CC) $(addprefix $(SRCb_d),$(SRCb_o)) -o $(ACHIEVb)

.c.o :
	$(CC) $(CFLAGS) -c $< -o $(basename $<).o

clean :
	rm -f $(addprefix $(SRC_d),$(SRC_o))
	rm -f $(addprefix $(SRCb_d),$(SRCb_o))

fclean : clean
	rm -f $(ACHIEV)
	rm -f $(ACHIEVb)

re : fclean all
