/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akihito <akihito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 22:50:28 by atomizaw          #+#    #+#             */
/*   Updated: 2022/03/09 00:35:24 by akihito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo_put_message(t_philo *philo, t_philo_status status)
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
	if (status == EAT)
	{
		printf("%ld %d %s\n", nowtime, idx, "has taken a fork");
		printf("%ld %d %s\n", nowtime, idx, "has taken a fork");
		printf("%ld %d %s\n", nowtime, idx, "is eating");
	}
	else if (status == THINK)
		printf("%ld %d %s\n", nowtime, philo->idx, "is thinking");
	else if (status == SLEEP)
		printf("%ld %d %s\n", nowtime, philo->idx, "is sleeping");
	else if (status == DIE)
		printf("%ld %d %s\n", nowtime, philo->idx, "died");
	pthread_mutex_unlock(mutex_write);
}

void	philo_usleep(const long usleep_time)
{
	struct timeval	now;
	long			now_time;
	struct timeval	start;
	long			start_time;
	long			usleep_halftime;

	gettimeofday(&start, NULL);
	start_time = start.tv_sec * 1000000 + start.tv_usec;
	gettimeofday(&now, NULL);
	now_time = now.tv_sec * 1000000 + now.tv_usec;
	usleep_halftime = usleep_time / 2;
	while (now_time - start_time < usleep_time)
	{
		usleep(usleep_halftime);
		gettimeofday(&now, NULL);
		now_time = now.tv_sec * 1000000 + now.tv_usec;
		usleep_halftime = (usleep_time - (now_time - start_time)) / 2;
	}
}
