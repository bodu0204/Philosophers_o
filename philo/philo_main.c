/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blyu <blyu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 13:21:24 by ryoakira          #+#    #+#             */
/*   Updated: 2022/07/23 14:23:58 by blyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	*philo(void *vp)
{
	t_philo		*p;
	t_schedule	s;

	p = vp;
	while (p->info->control == PREEXE)
		usleep(1);
	get_schedule(p->info, &s);
	philolog(p, THINK0);
	while (p->info->control == EXEING)
	{
		if (thinking(p, &s))
			return ((void *)DEAD);
		philolog(p, EAT);
		if (eating(p, &s))
			return ((void *)DEAD);
		philolog(p, SLEEP);
		if (sleeping(p, &s))
			return ((void *)DEAD);
		philolog(p, THINK);
	}
	p->status = DEAD;
	return ((void *)ALIVE);
}

int	thinking(t_philo *p, t_schedule	*s)
{
	unsigned long int	old_dt;
	int					f;

	if (p->info->control != EXEING)
		return (DEAD);
	old_dt = s->dt;
	f = NEXIST;
	get_schedule(p->info, s);
	while (old_dt > s->et && f == NEXIST)
	{
		if (p->lf.s == EXIST && p->next->lf.s == EXIST)
			f = rubfork(p);
		get_schedule(p->info, s);
	}
	if (f == NEXIST)
	{
		philolog(p, DIE);
		p->status = DEAD;
		return (DEAD);
	}
	return (ALIVE);
}

int	eating(t_philo *p, t_schedule	*s)
{
	unsigned long	n;

	if (p->info->control != EXEING)
	{
		p->status = DEAD;
		return (DEAD);
	}
	p->eat++;
	n = now();
	while (s->dt > n && s->st > n)
		n = now();
	if (s->dt < n)
	{
		philolog(p, DIE);
		p->status = DEAD;
	}
	pthread_mutex_lock(&(p->lf.m));
	p->lf.s = EXIST;
	pthread_mutex_unlock(&(p->lf.m));
	pthread_mutex_lock(&(p->next->lf.m));
	p->next->lf.s = EXIST;
	pthread_mutex_unlock(&(p->next->lf.m));
	return (p->status);
}

int	sleeping(t_philo *p, t_schedule	*s)
{
	unsigned long	n;

	if (p->info->control != EXEING)
	{
		p->status = DEAD;
		return (DEAD);
	}
	n = now();
	while (s->dt > n && s->tt > n)
		n = now();
	if (s->dt < n)
	{
		philolog(p, DIE);
		p->status = DEAD;
		return (DEAD);
	}
	return (ALIVE);
}
