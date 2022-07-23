/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blyu <blyu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 22:51:43 by blyu              #+#    #+#             */
/*   Updated: 2022/07/23 13:18:47 by blyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	philo_main(t_info *i, t_acsess *acs, t_sems *se)
{
	t_schedule		sc;
	unsigned int	eat;

	eat = 0;
	if (i->me == 0)
		sem_post(se->q);
	get_schedule(i, &sc);
	philolog(i, THINK0);
	while (1)
	{
		thinking(i, &sc, acs, se);
		philolog(i, EAT);
		eating(i, &sc, &eat, se);
		philolog(i, SLEEP);
		sleeping(i, &sc);
		philolog(i, THINK);
	}
	return ;
}

void	thinking(t_info *i, t_schedule	*sc, t_acsess *acs, t_sems *se)
{
	unsigned long int	old_dt;

	old_dt = sc->dt;
	*(acs->req) = 1;
	get_schedule(i, sc);
	while (!*(acs->res) && old_dt > sc->et)
		get_schedule(i, sc);
	if (old_dt <= sc->et)
	{
		philolog(i, DIE);
		if (*(acs->res))
			sem_post(se->f);
		exit(NORMAL);
	}
	*(acs->req) = 0;
	*(acs->res) = 0;
	return ;
}

void	eating(t_info *i, t_schedule *sc, unsigned int *eat, t_sems *se)
{
	unsigned long	n;

	(*eat)++;
	if (i->me == *eat)
		sem_post(se->q);
	n = now();
	while (sc->dt > n && sc->st > n)
		n = now();
	sem_post(se->f);
	if (sc->dt < n)
	{
		philolog(i, DIE);
		exit(NORMAL);
	}
	return ;
}

void	sleeping(t_info *i, t_schedule	*sc)
{
	unsigned long	n;

	n = now();
	while (sc->dt > n && sc->tt > n)
		n = now();
	if (sc->dt < n)
	{
		philolog(i, DIE);
		exit(NORMAL);
	}
	return ;
}
