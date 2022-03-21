/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomizaw <atomizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 14:51:38 by atomizaw          #+#    #+#             */
/*   Updated: 2022/03/19 23:01:22 by atomizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <stdlib.h>

int	main(int argc, char **argv)
{
	t_philo				*nil_philo;
	t_info				*info;

	if (!is_arg_ok(argc, argv))
	{
		return (0);
	}
	nil_philo = philo_nil_init();
	info = (t_info *)malloc(sizeof(t_info));
	argument_set(argc, argv, info);
	philo_init(info, nil_philo);
	philo_start(nil_philo, info->number_philo);
	philo_destory(nil_philo);
	free(nil_philo);
	free(info);
	return (0);
}

void	philo_destory(t_philo *nil)
{
	t_philo			*philo;
	t_philo			*tmp;
	pthread_mutex_t	*mutex_write;

	philo = nil->philo_right;
	mutex_write = philo->mutex_write;
	while (philo != nil)
	{
		tmp = philo;
		pthread_mutex_destroy(tmp->status->mutex);
		free(tmp->status->mutex);
		free(tmp->status);
		pthread_mutex_destroy(tmp->elapsed_time->mutex);
		free(tmp->elapsed_time->mutex);
		free(tmp->elapsed_time);
		pthread_mutex_destroy(tmp->fork_left->mutex);
		free(tmp->fork_left->mutex);
		free(tmp->fork_left);
		philo = philo->philo_right;
		free(tmp);
	}
	pthread_mutex_destroy(mutex_write);
	free(mutex_write);
}
