/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akihito <akihito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 17:10:24 by atomizaw          #+#    #+#             */
/*   Updated: 2022/03/09 22:33:31 by akihito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	argument_set(int argc, char **argv, t_info *info)
{
	info->number_philo = ft_atoi(argv[1]);
	info->die = ft_atoi(argv[2]) * 1000;
	info->eat = ft_atoi(argv[3]) * 1000;
	info->sleep = ft_atoi(argv[4]) * 1000;
	if (argc == 6)
		info->must_eat_count = ft_atoi(argv[5]);
	else
		info->must_eat_count = -1;
	return ;
}
