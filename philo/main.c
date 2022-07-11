
#include"philo.h"

int	main(int argc, char *argv[])
{
	t_philo		p;
	t_info		i;
	pthread_t	t;

	memset(&p, 0, sizeof(p));
	if (set_args(&i, argc, argv))
		return (1);
	i.control = PREEXE;
	p.info = &i;
	p.no = i.n;
	p.lf.s = EXIST;
	pthread_mutex_init(&(p.lf.m), NULL);
	if (set_args(&i, argc, argv))
		return (0);
	if (pthread_create(&t, NULL, philo, &p))
		i.control = ENDEXE;
	else
		mkphilo_and_exe(&p);
	pthread_mutex_destroy(&(p.lf.m));
	return (0);
}

int	set_args(t_info *i, int argc, char *argv[])
{
	int	err;

	err = 0;
	if (argc < 5 || argc > 6)
	{
		printf("arg error\n");
		return (1);
	}
	err += set_uint(argv[1], &(i->n));
	err += set_uint(argv[2], &(i->d));
	err += set_uint(argv[3], &(i->e));
	err += set_uint(argv[4], &(i->s));
	if (argc > 5)
		err += set_uint(argv[5], &(i->me));
	else
		i->me = 0;
	if (err)
	{
		printf("arg error\n");
		return (1);
	}
	if (!(i->n))
		return (1);
	return (0);
}

void	mkphilo_and_exe(t_philo *right)
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
		left->info->control = EXEING;
		exe(right);
		return ;
	}
	ft_memcpy(&p, right, sizeof(p));
	p.no--;
	p.next = right;
	pthread_mutex_init(&(p.lf.m), NULL);
	if (pthread_create(&t, NULL, philo, &p))
		p.info->control = ENDEXE;
	else
		mkphilo_and_exe(&p);
	pthread_mutex_destroy(&(p.lf.m));
	return ;
}

void	exe(t_philo *p)
{
	unsigned int	d;

	d = 0;
	while (d < p->info->n)
	{
		if (p->no == 1)
			d = 0;
		if (p->status == DEAD)
		{
			d++;
			died_philo(p);
		}
		p = p->next;
	}
	return ;
}

void	died_philo(t_philo *p)
{
	unsigned int	n;

	n = p->no;
	if (p->eat < p->info->me && p->info->control != ENDEXE)
	{
		p->info->control = ENDEXE;
		usleep((p->info->d) * 2);
		printf("philo%u just had eat %u times\n", p->no, p->eat);
	}
	else
	{
		p = p->next;
		while (p->no != n && p->info->control != ENDEXE)
		{
			if (p->eat < p->info->me)
			{
				p->info->control = ENDEXE;
				usleep((p->info->d) * 2);
				printf("philo%u just had eat %u times\n", p->no, p->eat);
			}
			p = p->next;
		}
	}
	return ;
}
