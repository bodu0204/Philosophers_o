/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blyu <blyu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:22:03 by blyu              #+#    #+#             */
/*   Updated: 2022/10/07 09:02:07 by blyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	philolog(t_philo *p, int d)
{
	if (p->info->control != EXEING)
		return ;
	if (d == THINK0)
		printf(LOGFMT, (unsigned)now(), p->no, "is thinking[start]");
	else if (d == THINK)
		printf(LOGFMT, (unsigned)now(), p->no, "is thinking");
	else if (d == EAT)
	{
		philolog(p, FORK);
		philolog(p, FORK);
		printf(LOGFMT, (unsigned)now(), p->no, "is eating");
	}
	else if (d == SLEEP)
		printf(LOGFMT, (unsigned)now(), p->no, "is sleeping");
	else if (d == DIE)
		printf(LOGFMT, (unsigned)now(), p->no, "died");
	else if (d == FORK)
		printf(LOGFMT, (unsigned)now(), p->no, "has taken a fork");
	fflush(stdout);
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
