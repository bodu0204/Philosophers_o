/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomizaw <atomizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 18:40:11 by akihito           #+#    #+#             */
/*   Updated: 2022/03/19 14:43:21 by atomizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	create_status(t_philo *new, int idx)
{
	new->idx = idx;
	new->status = (t_philo_mutex *)malloc(sizeof(t_philo_mutex));
	new->status->status = THINK;
	new->status->mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(new->status->mutex, NULL);
}

void	create_elapsed_time(t_philo *new)
{
	struct timeval	now_time;
	t_elapsed_time	*elapsed_time;

	elapsed_time = (t_elapsed_time *)malloc(sizeof(t_elapsed_time));
	gettimeofday(&now_time, NULL);
	elapsed_time->ms = now_time.tv_sec * 1000000 + now_time.tv_usec;
	elapsed_time->mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	new->elapsed_time = elapsed_time;
	pthread_mutex_init(elapsed_time->mutex, NULL);
}

void	create_fork_left(t_philo *new)
{
	new->fork_left = (t_fork_mutex *)malloc(sizeof(pthread_mutex_t));
	new->fork_left->status = TABLE;
	new->fork_left->mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(new->fork_left->mutex, NULL);
}
