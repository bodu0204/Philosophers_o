/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_put.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomizaw <atomizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 22:59:54 by atomizaw          #+#    #+#             */
/*   Updated: 2022/03/18 22:45:43 by atomizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo_putright(t_philo *philo)
{
	pthread_mutex_t	*mutex_fork;

	mutex_fork = philo->fork_right->mutex;
	pthread_mutex_lock(mutex_fork);
	if (philo->fork_right->status == RIGHT_HAND)
		philo->fork_right->status = TABLE;
	pthread_mutex_unlock(mutex_fork);
}

void	philo_putleft(t_philo *philo)
{
	pthread_mutex_t	*mutex_fork;

	mutex_fork = philo->fork_left->mutex;
	pthread_mutex_lock(mutex_fork);
	if (philo->fork_left->status == LEFT_HAND)
		philo->fork_left->status = TABLE;
	pthread_mutex_unlock(mutex_fork);
}
