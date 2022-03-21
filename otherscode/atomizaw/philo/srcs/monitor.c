/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomizaw <atomizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 15:23:07 by atomizaw          #+#    #+#             */
/*   Updated: 2022/03/19 14:39:55 by atomizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_monitor	dead_monitor(t_philo *philo, long *end_count)
{
	struct timeval	now;
	long			elasped_time;

	gettimeofday(&now, NULL);
	pthread_mutex_lock(philo->elapsed_time->mutex);
	elasped_time = philo->elapsed_time->ms;
	pthread_mutex_unlock(philo->elapsed_time->mutex);
	if (elasped_time < 0)
	{
		if (philo->status->status != FULL)
		{
			philo->status->status = FULL;
			(*end_count)++;
		}
		return (END);
	}
	else if (now.tv_sec * 1000000 + now.tv_usec
		- elasped_time >= philo->info->die)
	{
		philo_put_message(philo, DIE);
		return (STOP);
	}
	else
		return (RUNNING);
}

void	deal_deadlock(t_philo *philo)
{
	t_fork_status	fork_left_status;
	t_fork_status	fork_right_status;
	pthread_mutex_t	*fork_left_mutex;
	pthread_mutex_t	*fork_right_mutex;

	if (philo->fork_right == NULL)
		return ;
	fork_right_mutex = philo->fork_right->mutex;
	pthread_mutex_lock(fork_right_mutex);
	fork_right_status = philo->fork_right->status;
	pthread_mutex_unlock(fork_right_mutex);
	fork_left_mutex = philo->fork_left->mutex;
	pthread_mutex_lock(fork_left_mutex);
	fork_left_status = philo->fork_left->status;
	if (fork_left_status == LEFT_HAND && fork_right_status == LEFT_HAND)
		philo->fork_left->status = TABLE;
	pthread_mutex_unlock(fork_left_mutex);
}

int	is_stop(t_monitor action, t_philo *nil, t_philo *philo, long end)
{
	int		philo_num;

	philo_num = philo->info->number_philo;
	if (action != RUNNING)
	{
		if (action == STOP)
		{
			philo_stop(nil, philo, philo_num);
			return (TRUE);
		}
		if (action == END && end == philo->info->number_philo)
			return (TRUE);
	}
	deal_deadlock(philo);
	return (FALSE);
}

void	monitor_start(t_philo *nil)
{
	t_philo				*philo;
	t_monitor			action;
	long				end_count;

	philo = nil->philo_right;
	end_count = 0;
	while (1)
	{
		if (philo == nil)
		{
			philo = nil->philo_right;
			continue ;
		}
		action = dead_monitor(philo, &end_count);
		if (is_stop(action, nil, philo, end_count))
			return ;
		philo = philo->philo_right;
		usleep(50);
	}
}
