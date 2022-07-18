/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blyu <blyu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 22:51:51 by blyu              #+#    #+#             */
/*   Updated: 2022/07/18 22:51:52 by blyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	philo1(t_info *i, sem_t	*fk, sem_t	*qu, t_hand	*h);

void	philo(t_info *i)
{
	sem_t	*fk;
	sem_t	*qu;
	t_hand	h;

	fk = sem_open(FORKSEM, O_EXCL);
	qu = sem_open(QUOTASEM, O_EXCL);
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
	if (pthread_create(&p, NULL, philo_hand, h))
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
