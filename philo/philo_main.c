/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoakira <ryoakira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 13:21:24 by ryoakira          #+#    #+#             */
/*   Updated: 2022/07/15 16:08:49 by ryoakira         ###   ########.fr       */
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
		if (eating(p))
			return ((void *)DEAD);
		philolog(p, SLEEP);
		if (sleeping(p))
			return ((void *)DEAD);
		philolog(p, THINK);
	}
	p->status = DEAD;
	return ((void *)ALIVE);
}

void	get_schedule(t_info *i, t_schedule	*s)
{
	struct timezone	buff;
	struct timeval	now;

	gettimeofday(&now, &buff);
	s->et = (now.tv_usec / MS_US) + (now.tv_sec * S_MS);
	s->dt = s->et + i->d;
	return ;
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
		p->status = DEAD;
		philolog(p, DIE);
		return (DEAD);
	}
	return (ALIVE);
}

int	eating(t_philo *p)
{
	if (p->info->control != EXEING)
	{
		p->status = DEAD;
		return (DEAD);
	}
	p->eat++;
	if (p->info->d > p->info->e)
		usleep((p->info->e * S_MS) - TWEAK);
	else
	{
		usleep((p->info->d * S_MS) - TWEAK);
		p->status = DEAD;
		philolog(p, DIE);
	}
	pthread_mutex_lock(&(p->lf.m));
	p->lf.s = EXIST;
	pthread_mutex_unlock(&(p->lf.m));
	pthread_mutex_lock(&(p->next->lf.m));
	p->next->lf.s = EXIST;
	pthread_mutex_unlock(&(p->next->lf.m));
	return (p->status);
}

int	sleeping(t_philo *p)
{
	if (p->info->control != EXEING)
	{
		p->status = DEAD;
		return (DEAD);
	}
	if (p->info->d > p->info->e + p->info->s)
	{
		usleep((p->info->s * S_MS) - TWEAK);
		return (ALIVE);
	}
	else
	{
		usleep((p->info->d * S_MS) - TWEAK);
		p->status = DEAD;
		philolog(p, DIE);
		return (DEAD);
	}
}
