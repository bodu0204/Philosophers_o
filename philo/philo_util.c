/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blyu <blyu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:22:03 by blyu              #+#    #+#             */
/*   Updated: 2022/07/23 12:34:55 by blyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	philolog(t_philo *p, int d)
{
	unsigned int	t;

	if (p->info->control != EXEING)
		return ;
	t = now();
	if (d == THINK0)
		printf(LOGFMT, t, p->no, "is thinking[start]");
	else if (d == THINK)
		printf(LOGFMT, t, p->no, "is thinking");
	else if (d == EAT)
	{
		philolog(p, FORK);
		philolog(p, FORK);
		printf(LOGFMT, t, p->no, "is eating");
	}
	else if (d == SLEEP)
		printf(LOGFMT, t, p->no, "is sleeping");
	else if (d == DIE)
		printf(LOGFMT, t, p->no, "died");
	else if (d == FORK)
		printf(LOGFMT, t, p->no, "has taken a fork");
	return ;
}

int	rubfork(t_philo *p)
{
	pthread_mutex_lock(&(p->lf.m));
	if (p->lf.s == EXIST)
	{
		p->lf.s = NEXIST;
		pthread_mutex_unlock(&(p->lf.m));
		pthread_mutex_lock(&(p->next->lf.m));
		if (p->next->lf.s == EXIST)
		{
			p->next->lf.s = NEXIST;
			pthread_mutex_unlock(&(p->next->lf.m));
			return (EXIST);
		}
		else
		{
			pthread_mutex_unlock(&(p->next->lf.m));
			pthread_mutex_lock(&(p->lf.m));
			p->lf.s = EXIST;
			pthread_mutex_unlock(&(p->lf.m));
		}
	}
	else
		pthread_mutex_unlock(&(p->lf.m));
	return (NEXIST);
}

void	get_schedule(t_info *i, t_schedule	*s)
{
	s->et = now();
	s->dt = s->et + i->d;
	s->st = s->et + i->e;
	s->tt = s->st + i->s;
	return ;
}

unsigned long int	now(void)
{
	struct timezone	buff;
	struct timeval	now;

	gettimeofday(&now, &buff);
	return ((now.tv_usec / MS_US) + (now.tv_sec * S_MS));
}
