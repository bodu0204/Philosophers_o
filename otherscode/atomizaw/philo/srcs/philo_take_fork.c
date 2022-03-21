/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_take_fork.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akihito <akihito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 19:35:32 by atomizaw          #+#    #+#             */
/*   Updated: 2022/03/12 15:00:36 by akihito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	take_fork_left(t_philo *philo)
{
	if (philo->fork_left->status == TABLE)
	{
		philo->fork_left->status = LEFT_HAND;
		return (TRUE);
	}
	else
		return (FALSE);
}

int	take_fork_right(t_philo *philo)
{
	if (philo->fork_right->status == TABLE)
	{
		philo->fork_right->status = RIGHT_HAND;
		return (TRUE);
	}
	else
		return (FALSE);
}

int	philo_takeleft(t_philo *philo)
{
	pthread_mutex_t	*mutex_fork;

	while (TRUE)
	{
		mutex_fork = philo->fork_left->mutex;
		pthread_mutex_lock(mutex_fork);
		if (take_fork_left(philo))
		{
			pthread_mutex_unlock(mutex_fork);
			break ;
		}
		else
		{
			pthread_mutex_unlock(mutex_fork);
			if (wait_moment(philo))
				return (TRUE);
		}
	}
	return (FALSE);
}

int	philo_takeright(t_philo *philo)
{
	int				next_action;
	pthread_mutex_t	*mutex_fork;

	mutex_fork = NULL;
	if (only_1_philo(philo))
		return (TRUE);
	while (1)
	{
		next_action = philo_action(philo, mutex_fork);
		if (next_action == CONTINUE)
			continue ;
		else if (next_action == BREAK)
			break ;
		else
			return (TRUE);
	}
	return (FALSE);
}

int	philo_takeleft_again(t_philo *philo)
{
	pthread_mutex_t	*mutex_fork;

	mutex_fork = philo->fork_left->mutex;
	pthread_mutex_lock(mutex_fork);
	if (philo->fork_left->status == LEFT_HAND)
		pthread_mutex_unlock(mutex_fork);
	else
	{
		pthread_mutex_unlock(mutex_fork);
		if (philo_takeleft(philo))
			return (DEAD);
	}
	return (FALSE);
}
