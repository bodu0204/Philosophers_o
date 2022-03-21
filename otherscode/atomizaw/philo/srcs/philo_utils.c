/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akihito <akihito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 21:50:27 by atomizaw          #+#    #+#             */
/*   Updated: 2022/03/12 14:15:14 by akihito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	philo_action(t_philo *philo, pthread_mutex_t *mutex_fork)
{
	if (philo->fork_right)
		mutex_fork = philo->fork_right->mutex;
	else
	{
		if (wait_moment(philo))
			return (DEAD);
		return (CONTINUE);
	}
	pthread_mutex_lock(mutex_fork);
	if (take_fork_right(philo))
	{
		pthread_mutex_unlock(mutex_fork);
		return (BREAK);
	}
	else
	{
		pthread_mutex_unlock(mutex_fork);
		if (wait_moment(philo))
			return (DEAD);
		return (CONTINUE);
	}
}

int	wait_moment(t_philo *philo)
{
	pthread_mutex_t	*mutex_status;

	usleep(50);
	mutex_status = philo->status->mutex;
	pthread_mutex_lock(mutex_status);
	if (philo->status->status == DIE)
	{
		pthread_mutex_unlock(mutex_status);
		return (TRUE);
	}
	pthread_mutex_unlock(mutex_status);
	return (FALSE);
}

int	only_1_philo(t_philo *philo)
{
	struct timeval	now;
	pthread_mutex_t	*mutex_write;
	long			nowtime;
	int				idx;

	idx = philo->idx;
	mutex_write = philo->mutex_write;
	pthread_mutex_lock(mutex_write);
	gettimeofday(&now, NULL);
	nowtime = (now.tv_sec * 1000000 + now.tv_usec) / 1000;
	if (philo->info->number_philo == 1)
	{
		printf("%ld %d %s\n", nowtime, idx, "has taken a fork");
		pthread_mutex_unlock(mutex_write);
		usleep(philo->info->die);
		return (TRUE);
	}
	pthread_mutex_unlock(mutex_write);
	return (FALSE);
}
