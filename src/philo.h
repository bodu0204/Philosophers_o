#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>

# define TWEAK 0
//flag about control thread
# define PREEXE 0
# define EXEING 1
# define ENDEXE 2
//flag about is fork exist
# define NEXIST 0
# define EXIST 1
//flag about is philo alive
# define ALIVE 0
# define DEAD 1
//flag about what philo doing
# define THINK0 0
# define THINK 1
# define DIE 2
# define EAT 3
# define SLEEP 4
# define FORK 5
//convert unit
# define S_US 1000000
# define S_MS 1000
# define MS_US 1000
//log format
# define LOGFMT "%u_in_ms %u %s\n"

typedef struct s_info
{
	unsigned int		n;
	unsigned int		d;
	unsigned int		e;
	unsigned int		s;
	unsigned int		me;
	int					control;
}	t_info;

typedef struct s_fork
{
	pthread_mutex_t	m;
	int				s;
}	t_fork;

typedef struct s_philo
{
	unsigned int	no;
	struct s_fork	lf;
	unsigned int	eat;
	int				status;
	struct s_philo	*next;
	struct s_info	*info;
}	t_philo;

typedef struct s_schedule
{
	unsigned long int	et;
	unsigned long int	dt;
}	t_schedule;
//main.c
void	mkphilo_and_exe(t_philo *right);
void	exe(t_philo *p);
void	end_exe(t_philo *p);
void	died_philo(t_philo *p);
//philo.c
void	*philo(void *vp);
int		thinking(t_philo *p, t_schedule	*s);
int		eating(t_philo *p);
int		sleeping(t_philo *p);
//philo_util.c
int		rubfork(t_philo *p);
void	get_schedule(t_info *i, t_schedule	*s);
void	philolog(t_philo *p, int d);
//tool.c
void	*ft_memcpy(void *dst, const void *src, size_t n);
int		set_args(t_info *i, int argc, char *argv[]);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		set_uint(char	*s, unsigned int *u);
#endif

/* 
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
	struct s_fork	lf;		//philo's fork at left
	unsigned int	eat;	//times eated
	int				status;	//is philo alive
	struct s_philo	*next;	//philo next to
	struct s_info	*info;	//prerequisite information
}	t_philo;

typedef struct s_schedule
{
	unsigned long int	et;		//time eated
	unsigned long int	dt;		//time to die
}	t_schedule;
 */