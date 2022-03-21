/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomizaw <atomizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 18:39:29 by atomizaw          #+#    #+#             */
/*   Updated: 2022/03/19 14:43:38 by atomizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philo	*philo_create(int idx, t_info *info, pthread_mutex_t *mutex_write)
{
	t_philo			*new;

	new = (t_philo *)malloc(sizeof(t_philo));
	create_status(new, idx);
	new->info = info;
	create_elapsed_time(new);
	new->must_eat_count = info->must_eat_count;
	create_fork_left(new);
	new->fork_right = NULL;
	new->philo_left = NULL;
	new->philo_right = NULL;
	new->mutex_write = mutex_write;
	return (new);
}

t_philo	*philo_nil_init(void)
{
	t_philo	*nil_philo;

	nil_philo = (t_philo *)malloc(sizeof(t_philo));
	nil_philo->idx = 0;
	nil_philo->status = NULL;
	nil_philo->info = NULL;
	nil_philo->elapsed_time = NULL;
	nil_philo->must_eat_count = 0;
	nil_philo->fork_left = NULL;
	nil_philo->fork_right = NULL;
	nil_philo->philo_left = nil_philo;
	nil_philo->philo_right = nil_philo;
	return (nil_philo);
}

void	philo_append(t_philo *nil, t_philo *new_philo)
{
	t_philo	*last;

	last = nil->philo_left;
	new_philo->philo_left = last;
	last->philo_right = new_philo;
	last->fork_right = new_philo->fork_left;
	new_philo->philo_left = last;
	new_philo->philo_right = nil;
	new_philo->fork_right = nil->philo_right->fork_left;
	nil->philo_left = new_philo;
}

void	philo_init(t_info *info, t_philo *nil_philo)
{
	t_philo			*new_philo;
	pthread_mutex_t	*mutex_write;
	int				idx;

	mutex_write = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(mutex_write, NULL);
	idx = 0;
	while (idx < info->number_philo)
	{
		new_philo = philo_create(idx + 1, info, mutex_write);
		philo_append(nil_philo, new_philo);
		idx++;
	}
	return ;
}
