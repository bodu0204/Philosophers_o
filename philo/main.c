/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blyu <blyu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 16:58:02 by blyu              #+#    #+#             */
/*   Updated: 2022/07/23 12:35:14 by blyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

int	main(int argc, char *argv[])
{
	t_philo		p;
	t_info		i;
	pthread_t	t;

	memset(&p, 0, sizeof(p));
	if (set_args(&i, argc, argv))
		return (0);
	i.control = PREEXE;
	p.info = &i;
	p.no = i.n;
	p.lf.s = EXIST;
	pthread_mutex_init(&(p.lf.m), NULL);
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
	if (err || i->n >= 2048)
	{
		printf("arg error\n");
		return (1);
	}
	if (!(i->n) || (argc > 5 && !i->me))
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
	unsigned int	e;

	d = 0;
	e = 0;
	while (d < p->info->n && p->info->control != ENDEXE)
	{
		if (p->no == 1)
		{
			d = 0;
			e = 0;
		}
		if (p->status == DEAD)
			d++;
		if (p->eat >= p->info->me)
			e++;
		if ((p->info->me && e >= p->info->n) \
		|| (!p->info->me && p->status == DEAD))
			p->info->control = ENDEXE;
		p = p->next;
	}
	usleep(p->info->d * MS_US * 2);
	return ;
}
