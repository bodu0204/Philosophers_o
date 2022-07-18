
#include"philo.h"

void	philo1(t_info *i, sem_t	*fk, sem_t	*qu, t_hand	*h);
void	philo(t_info *i)
{
	sem_t	*fk;
	sem_t	*qu;
	t_hand	h;
	
	fk = sem_open(FORK, O_EXCL);
	qu = sem_open(QUOTA, O_EXCL);
	if (fk == SEM_FAILED || qu == SEM_FAILED)
	{
		printf("sem_open error");
		exit(ERROR);
	}
	philo1(i, fk, qu, &h);
	exit(NORMAL);
}

void	philo1(t_info *i, sem_t	*fk, sem_t	*qu, t_hand	*h)
{
	int			reqest;
	int			respos;
	t_acsess	a;
	pthread_t	p;
	t_sems		s;

	reqest = 0;
	respos = 0;
	a.req = &reqest;
	a.res = &respos;
	h->f = fk;
	h->req = &reqest;
	h->res = &respos;
	s.f = fk;
	s.q = qu;
	if (pthread_create(&p, NULL, philo_hand, &h))
	{
		printf("pthread_create error");
		exit(ERROR);
	}
	philo_main(i, &a, &s);
	exit(NORMAL);
}

void	*philo_hand(void *vp)
{
	t_hand	*h;

	h = vp;
	while (1)
	{
		*(h->req) = 0;
		while (!*(h->req))
			usleep(1);
		*(h->req) = 0;
		sem_wait(h->f);
		*(h->res) = 1;
	}
	return (NULL);
}
void	philo_main(t_info *i, t_acsess *acs, t_sems *se)
{
	t_schedule		sc;
	unsigned int	eat;

	eat = 0;
	if (i->e == 0)
		sem_post(se->q);
	get_schedule(i, &sc);
	philolog(i, THINK0);
	while (1)
	{
		thinking(i, &sc, acs, se);
		philolog(i, EAT);
		eating(i, &sc, &eat, se);
		philolog(i, SLEEP);
		sleeping(i, &sc);
		philolog(i, THINK);
	}
	return ;
}

void	thinking(t_info *i, t_schedule	*sc, t_acsess *acs, t_sems *se)
{
	unsigned long int	old_dt;
		
	old_dt = sc->dt;
	*(acs->req) = 1;
	get_schedule(i, sc);
	while (!*(acs->res) && old_dt > sc->et)
		get_schedule(i, sc);
	if (!*(acs->res))
	{
		philolog(i, DIE);
		if (*(acs->res))
			sem_post(se->f);
		exit(NORMAL);
	}
	*(acs->req) = 0;
	*(acs->res) = 0;
	return ;
}

void	eating(t_info *i, t_schedule	*sc, unsigned int *eat, t_sems *se)
{
	unsigned long	n;

	*eat++;
	if (i->e == *eat)
		sem_post(se->q);
	n = now();
	while (sc->dt > n && sc->st > n)
		n = now();
	sem_post(se->f);
	if (sc->dt < n)
	{
		philolog(i, DIE);
		exit(NORMAL);
	}
	return ;
}

void	sleeping(t_info *i, t_schedule	*sc)
{
	unsigned long	n;

	n = now();
	while (sc->dt > n && sc->tt > n)
		n = now();
	if (sc->dt < n)
	{
		philolog(i, DIE);
		exit(NORMAL);
	}
	return ;
}
