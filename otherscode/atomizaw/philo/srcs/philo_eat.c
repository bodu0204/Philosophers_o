/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomizaw <atomizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 22:41:41 by atomizaw          #+#    #+#             */
/*   Updated: 2022/03/14 13:29:14 by atomizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	philo_start_eat(t_philo *philo)
{
	struct timeval	now;
	pthread_mutex_t	*mutex_status;
	pthread_mutex_t	*mutex_elapsed_time;

	philo_put_message(philo, EAT);
	gettimeofday(&now, NULL);
	mutex_elapsed_time = philo->elapsed_time->mutex;
	pthread_mutex_lock(mutex_elapsed_time);
	philo->elapsed_time->ms = now.tv_sec * 1000000 + now.tv_usec;
	pthread_mutex_unlock(mutex_elapsed_time);
	philo_usleep(philo->info->eat);
	mutex_status = philo->status->mutex;
	pthread_mutex_lock(mutex_status);
	if (philo->status->status == DIE)
	{
		pthread_mutex_unlock(mutex_status);
		return (DEAD);
	}
	pthread_mutex_unlock(mutex_status);
	philo_put_message(philo, SLEEP);
	return (FALSE);
}
