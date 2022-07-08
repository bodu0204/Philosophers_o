#include"debug.h"
#include"philo.h"

int	main(int argc, char *argv[])
{
	t_philo			p;
	t_info			i;
	pthread_mutex_t	m;
	pthread_t		t;

	bzero(&p, sizeof(p));/* memesetに */
	if (set_args(&i, argc, argv))
		return (1);
	i.control = PREEXE;
	p.info = &i;
	p.no = i.n;
	pthread_mutex_init(&(p.lf), NULL);
	if (set_args(&i, argc, argv))
		return (1);
	pthread_create(&t, NULL, philo, &p);
	mkphilo_and_exe(&p);
	return (0);
}

int set_args(t_info *i, int argc, char *argv[])
{
	if (argc < 4 || argc > 5)
		return (1);
	if (set_uint(argv[1], &(i->n)))
		return (1);
	if (set_uint(argv[2], &(i->d)))
		return (1);
	if (set_uint(argv[3], &(i->s)))
		return (1);
	if (argc > 4)
	{
		if (set_uint(argv[4], &(i->me)))
			return (1);
	}
	return (0);
}

void mkphilo_and_exe(t_philo *right)
{
	t_philo		p;
	t_philo		*left;
	pthread_t	t;

	if (right->no <= 1)
	{
		left = right;
		while (left->next)
			left = left->next;
		left->next = right;
		exe();
		return ;
	}
	memcpy(&p, right, sizeof(p));/*  */
	p.no--;
	p.next = right;
	pthread_mutex_init(&(p.lf.m), NULL);
	pthread_create(&t, NULL, philo, &p);
	mkphilo_and_exe(&p);
	pthread_mutex_destroy(&(p.lf.m));
	return ;
}

void	*philo(void *vp)
{
	t_philo			*p;
	struct timeval	dt;

	p = vp;
	while (p->info->control == PREEXE)
		usleep(1);
	get_dt(p->info, &dt);
	while (p->info->control == EXEING)
	{
//thinking
		
//eating

//sleeping
	}
	return ((void *)ALIVE);
}

int	thinking(t_philo *p, struct timeval *dt)
{
	struct timeval	now;
	struct timezone	buff;
	int				f;

	gettimeofday(&now, &buff);
	printf("thinking\n");
	f = NEXIST;
	while(p->info->control == EXEING && f == NEXIST)
	{
		gettimeofday(&now, &buff);
		if ((dt->tv_sec < now.tv_sec) || \
		(dt->tv_sec == now.tv_sec && dt->tv_usec < now.tv_usec))
			return (DEAD);
		f = rubfork(p);
	}
	return (ALIVE);
}

void	get_dt(t_info *i, struct timeval *dt)
{
	struct timezone	buff;

	gettimeofday(dt, &buff);
	dt->tv_usec += (i->d * 1000);
	dt->tv_sec += dt->tv_usec / 1000000;
	dt->tv_usec = dt->tv_usec % 1000000;
	return ;
}
int eating_sleeping (t_philo *p, struct timeval *dt)
{
	struct timeval	now;
	struct timezone	buff;

	gettimeofday(&now, &buff);
	printf("thinking\n");
	if ()
	memcpy(&now, dt, sizeof(struct timeval));
	dt->tv_usec += (p->info->d * 1000);
	dt->tv_sec += dt->tv_usec / 1000000;
	dt->tv_usec = dt->tv_usec % 1000000;
}
int	rubfork(t_philo *p)
{
	if (p->lf.s == EXIST && p->next->lf.s == EXIST)
	{
		pthread_mutex_lock(&(p->lf.m));
		if (p->lf.s == EXIST)
		{
			p->lf.s == NEXIST;
			pthread_mutex_unlock(&(p->lf.m));
			pthread_mutex_lock(&(p->next->lf.m));
			if (p->next->lf.s == EXIST)
			{
				p->next->lf.s == NEXIST;
				pthread_mutex_unlock(&(p->next->lf.m));
				return (EXIST);
			}
			else
			{
				pthread_mutex_unlock(&(p->next->lf.m));
				pthread_mutex_lock(&(p->lf.m));
				p->lf.s == EXIST;
				pthread_mutex_unlock(&(p->lf.m));
			}
		}
		else
			pthread_mutex_unlock(&(p->lf.m));
	}
	return (NEXIST);
}