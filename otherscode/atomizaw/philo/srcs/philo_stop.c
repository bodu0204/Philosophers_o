/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_stop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomizaw <atomizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 16:57:10 by atomizaw          #+#    #+#             */
/*   Updated: 2022/03/02 22:25:07 by atomizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo_stop(t_philo *nil, t_philo *philo, int philo_number)
{
	int				idx;
	pthread_mutex_t	*mutex_status;

	idx = 0;
	while (idx < philo_number)
	{
		if (philo == nil)
		{
			philo = philo->philo_right;
			continue ;
		}
		mutex_status = philo->status->mutex;
		pthread_mutex_lock(mutex_status);
		philo->status->status = DIE;
		pthread_mutex_unlock(mutex_status);
		idx++;
		philo = philo->philo_right;
	}
}
