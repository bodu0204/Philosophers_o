#ifndef PHILO_H
# define PHILO_H
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_info
{
	unsigned int		n;		//number_of_philosophers
	unsigned int		d;		//time_to_die
	unsigned int		e;		//time_to_eat
	unsigned int		s;		//time_to_sleep
	unsigned int		me;		//number of times each philosopher must eat
	int					control;//control thread flag
}	t_info;

typedef struct s_fork
{
	pthread_mutex_t	m;	//fork's mutex
	int				s;	//status
}	t_fork;

typedef struct s_philo
{
	unsigned int	no;		//philo nomber
	t_fork			lf;		//philo's fork at left
	unsigned int	eat;	//times eated
	int				status;	//is philo alive
	struct s_philo	*next;	//philo next to
	struct s_info	*info;	//prerequisite information
}	t_philo;

#define TWEAK 2

//flag about control thread
#define PREEXE 0
#define EXEING 1
#define ENDEXE 2

//flag about is fork exist
#define NEXIST 0
#define EXIST 1

//flag about is philo alive
#define ALIVE 0
#define DEAD 1

int	set_args(t_info *i, int argc, char *argv[]);
int	set_uint(char	*s, unsigned int *u);

void	*philo(void *vp);

void	exe(t_philo *p);
int	rubfork(t_philo *p);
int eating_sleeping (t_philo *p, struct timeval *dt);
void	get_dt(t_info *i, struct timeval *dt);
int	thinking(t_philo *p, struct timeval *dt);
void mkphilo_and_exe(t_philo *right);
int set_args(t_info *i, int argc, char *argv[]);
void	putfork(t_philo *p);

#endif
