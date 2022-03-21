/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_satisfied.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akihito <akihito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 16:47:19 by atomizaw          #+#    #+#             */
/*   Updated: 2022/03/06 20:15:39 by akihito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo_satisfied(t_philo *philo)
{
	pthread_mutex_t	*mutex_elapsed_time;

	mutex_elapsed_time = philo->elapsed_time->mutex;
	pthread_mutex_lock(mutex_elapsed_time);
	philo->elapsed_time->ms = SATISFIED;
	pthread_mutex_unlock(mutex_elapsed_time);
	return ;
}
