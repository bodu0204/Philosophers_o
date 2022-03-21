/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start_sleep.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akihito <akihito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 16:10:29 by atomizaw          #+#    #+#             */
/*   Updated: 2022/03/06 21:21:58 by akihito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	philo_start_sleep(t_philo *philo, int next_think)
{
	pthread_mutex_t	*mutex_status;

	philo_usleep(philo->info->sleep);
	mutex_status = philo->status->mutex;
	pthread_mutex_lock(mutex_status);
	if (philo->status->status == DIE)
	{
		pthread_mutex_unlock(mutex_status);
		return (TRUE);
	}
	pthread_mutex_unlock(mutex_status);
	if (next_think)
		philo_put_message(philo, THINK);
	return (FALSE);
}
