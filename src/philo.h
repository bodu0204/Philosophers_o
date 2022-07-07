#ifndef PHILO_H
# define PHILO_H
#include <unistd.h>
#include <string.h>
#include <pthread.h>

typedef struct s_info
{
	unsigned int		n;		//number_of_philosophers
	unsigned int		d;		//time_to_die
	unsigned int		e;		//time_to_eat
	unsigned int		s;		//time_to_sleep
	unsigned int		me;		//number of times each philosopher must eat
	int					control;//control　thread flag
}	t_info;

typedef struct s_philo
{
	unsigned int	no;			//philo nomber
	pthread_mutex_t	lf;			//philo's fork at left
	unsigned int	eat;		//times eatred
	struct s_philo	*next;		//philo next to
	struct s_info	*info;		//prerequisite information
}	t_philo;

int	set_args(t_info *i, int argc, char *argv[]);
int	set_uint(char	*s, unsigned int *u);

void	*philo(void *vp);
#endif
