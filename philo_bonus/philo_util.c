/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blyu <blyu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:22:03 by blyu              #+#    #+#             */
/*   Updated: 2022/07/18 20:51:12 by blyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	philolog(t_info *i, int d)
{
	unsigned int	t;

	t = now();
	if (d == THINK0)
		printf(LOGFMT, t, i->n, "is thinking[start]");
	else if (d == THINK)
		printf(LOGFMT, t, i->n, "is thinking");
	else if (d == EAT)
	{
		philolog(i, FORK);
		philolog(i, FORK);
		printf(LOGFMT, t, i->n, "is eating");
	}
	else if (d == SLEEP)
		printf(LOGFMT, t, i->n, "is sleeping");
	else if (d == DIE)
		printf(LOGFMT, t, i->n, "died");
	else if (d == FORK)
		printf(LOGFMT, t, i->n, "has taken a fork");
	return ;
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
