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
	i.control = 1;
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
	pthread_mutex_init(&(p.lf), NULL);
	pthread_create(&t, NULL, philo, &p);
	mkphilo_and_exe(&p);
	return ;
}

void	*philo(void *vp)
{
	t_philo	*p;

	p = vp;
	while (p->info->control)
		usleep(1);
	while ()
	{
		/* code */
	}
	


}
