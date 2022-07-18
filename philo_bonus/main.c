/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blyu <blyu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 22:51:38 by blyu              #+#    #+#             */
/*   Updated: 2022/07/18 22:51:39 by blyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

int	main(int argc, char *argv[])
{
	t_info		i;
	t_quota		q;
	sem_t		*s;
	pthread_t	p;
	int			quota;

	if (set_args(&i, argc, argv))
		return (0);
	sem_unlink(FORKSEM);
	sem_unlink(QUOTASEM);
	q.pn = i.n;
	q.s = sem_open(QUOTASEM, O_CREAT, S_IRWXU | S_IRWXG, 0);
	if (q.s == SEM_FAILED)
		return (1);
	s = sem_open(FORKSEM, O_CREAT, S_IRWXU | S_IRWXG, (int)i.n / 2);
	if (s == SEM_FAILED)
		return (1);
	quota = NOTYET;
	q.f = &quota;
	if (pthread_create(&p, NULL, main_quota, &q))
		return (1);
	mkphilo_and_exe(&i, &quota);
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
		i->me = __UINT32_MAX__;
	if (err || i->n >= 2048)
	{
		printf("arg error\n");
		return (1);
	}
	if (!(i->n))
		return (1);
	return (0);
}

void	*main_quota(void *vp)
{	
	t_quota			*q;
	unsigned int	x;

	q = vp;
	x = 0;
	while (x < q->pn)
	{
		sem_wait(q->s);
		x++;
	}
	*(q->f) = FINISH;
	return (NULL);
}

void	mkphilo_and_exe(t_info *i, int *quota)
{
	unsigned int	x;
	pid_t			p;

	x = 0;
	while (x < i->n)
	{
		p = fork();
		if (p < 0)
		{
			printf("fork error");
			kill (0, SIGINT);
			exit(1);
		}
		x++;
		if (p == 0)
		{
			i->n = x;
			philo(i);
		}
		else if (x >= i->n)
			exe(i, quota);
	}
	return ;
}

void	exe(t_info *i, int *quota)
{
	unsigned int	d;
	int				status;

	d = 0;
	while (d < i->n)
	{
		waitpid(-1, &status, 0);
		if (status == ERROR || *quota == NOTYET)
			kill (0, SIGINT);
		d++;
	}
	return ;
}
